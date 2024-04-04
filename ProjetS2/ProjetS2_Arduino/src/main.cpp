/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Fevrier 2022
*/

/*------------------------------ Librairies ---------------------------------*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>
#include <ADXL335.h>
/*------------------------------ Constantes ---------------------------------*/

#define BAUD 256000        // Frequence de transmission serielle
#define ROT_DT 3
#define ROT_CLK 2
#define ROT_BUT 8

#define LCD_ROWS 16
#define LCD_COLUMNS 2

#define LCD_RS 49
#define LCD_RW 47
#define LCD_E 45

#define LCD_D0 51
#define LCD_D1 53
#define LCD_D2 50
#define LCD_D3 52

#define LCD_D4 43
#define LCD_D5 41
#define LCD_D6 39
#define LCD_D7 37


#define X_AXIS_PIN A0
#define Y_AXIS_PIN A1
#define Z_AXIS_PIN A2

#define PWM_PIN PH5


#define SEG_A_CENT 22
#define SEG_B_CENT 24
#define SEG_C_CENT 26
#define SEG_D_CENT 28
#define SEG_E_CENT 30
#define SEG_F_CENT 32
#define SEG_G_CENT 34

#define SEG_A_DIZ 23
#define SEG_B_DIZ 25
#define SEG_C_DIZ 27
#define SEG_D_DIZ 29
#define SEG_E_DIZ 31
#define SEG_F_DIZ 33
#define SEG_G_DIZ 35

#define SEG_A_UNI 36
#define SEG_B_UNI 38
#define SEG_C_UNI 40
#define SEG_D_UNI 42
#define SEG_E_UNI 44
#define SEG_F_UNI 46
#define SEG_G_UNI 48

/*---------------------------- Variables globales ---------------------------*/

volatile bool shouldSend_ = false;  // Drapeau prêt à envoyer un message
volatile bool shouldRead_ = false;  // Drapeau prêt à lire un message

LiquidCrystal lcd(LCD_RS, LCD_E,
		LCD_D0, LCD_D1, LCD_D2, LCD_D3,
		LCD_D4, LCD_D5, LCD_D6, LCD_D7);

int pinout_cent[7] = {  SEG_A_CENT,
                        SEG_B_CENT,
                        SEG_C_CENT,
                        SEG_D_CENT,
                        SEG_E_CENT,
                        SEG_F_CENT,
                        SEG_G_CENT
                      };


int pinout_diz[7] = { SEG_A_DIZ,
                      SEG_B_DIZ,
                      SEG_C_DIZ,
                      SEG_D_DIZ,
                      SEG_E_DIZ,
                      SEG_F_DIZ,
                      SEG_G_DIZ
                    };


int pinout_uni[7] = { SEG_A_UNI,
                      SEG_B_UNI,
                      SEG_C_UNI,
                      SEG_D_UNI,
                      SEG_E_UNI,
                      SEG_F_UNI,
                      SEG_G_UNI
                    };

int * ptr_pinout[3] = {pinout_cent,pinout_diz,pinout_uni};


                   //a,b,c,d,e,f,g
int BCD[10][7] = {  {0,0,0,0,0,0,1},  //0
                    {1,0,0,1,1,1,1},  //1
                    {0,0,1,0,0,1,0},  //2
                    {0,0,0,0,1,1,0},  //3
                    {1,0,0,1,1,0,0},  //4
                    {0,1,0,0,1,0,0},  //5
                    {1,1,0,0,0,0,0},  //6
                    {0,0,0,1,1,1,1},  //7
                    {0,0,0,0,0,0,0},  //8
                    {0,0,0,1,1,0,0}   //9
                  };

int result_A[5] = {0};
uint32_t result_A_temp[3] = {0};


char buff[64] = {0};

char displayed = 0;

int previousCount = 0;
int rotationCount = 0;

int threshold_accel = 10;

bool movement = false;
bool temp_mov = false;

int score = 0;


/*------------------------- Prototypes de fonctions -------------------------*/
void sendMsg(); 
void readMsg();
void serialEvent();
bool readAccel();
void display7Seg();
int print_BCD(int number);
/*---------------------------- Fonctions "Main" -----------------------------*/

void setup() {
  Serial.begin(BAUD);               // Initialisation de la communication serielle
  Serial1.begin(BAUD);  

  pinMode(PWM_PIN, OUTPUT);
  analogWrite(PWM_PIN, 80);
  for(int i = 0; i < 3 ; i++){ //SET PINT 7-SEG
    for(int y = 0; y < 7; y++){
      pinMode(*(ptr_pinout[i] + y), OUTPUT);
      digitalWrite(*(ptr_pinout[i] + y), LOW);
    }

  }

 // pinMode(pinLED, OUTPUT);
 // digitalWrite(pinLED, ledState);
}

/* Boucle principale (infinie) */
void loop() {

  if(shouldRead_){
    readMsg();
    sendMsg();
  }

  movement = readAccel();
  display7Seg();
  //Serial.println(potValue);          // debug
  delay(10);  // delais de 10 ms

}

/*---------------------------Definition de fonctions ------------------------*/

void serialEvent() { shouldRead_ = true; }


/*---------------------------Definition de fonctions ------------------------
Fonction d'envoi
Entrée : Aucun
Sortie : Aucun
Traitement : Envoi du message
-----------------------------------------------------------------------------*/
void sendMsg() {
  StaticJsonDocument<500> doc;
  // Elements du message
  doc["time"] = millis();
  doc["mov"] = movement;

  // Serialisation
  serializeJson(doc, Serial);

  // Envoie
  Serial.println();
  shouldSend_ = false;
}

/*---------------------------Definition de fonctions ------------------------
Fonction de reception
Entrée : Aucun
Sortie : Aucun
Traitement : Réception du message
-----------------------------------------------------------------------------*/
void readMsg(){
  // Lecture du message Json
  StaticJsonDocument<500> doc;
  JsonVariant parse_msg;

  // Lecture sur le port Seriel
  DeserializationError error = deserializeJson(doc, Serial);
  shouldRead_ = false;

  // Si erreur dans le message
  if (error) {
    Serial.print("deserialize() failed: ");
    Serial.println(error.c_str());
    return;
  }
  
  // Analyse des éléments du message message
  parse_msg = doc["7Seg"];
  score = (int)parse_msg;
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    display7Seg();
  }
}


bool readAccel() {
            temp_mov = false;
            result_A_temp[0] = analogRead(A0);
            for(int y = 0; y < 9; y++)
            {
               result_A_temp[0] += analogRead(A0);
            }
            result_A[0] = result_A_temp[0]/10;
              
  
            result_A_temp[1] = analogRead(A1);
            for(int y = 0; y < 9; y++)
            {
              result_A_temp[1] += analogRead(A1);
            }              
            result_A[1] = result_A_temp[1]/10;
              
            
            result_A_temp[2] = analogRead(A2);
            for(int y = 0; y < 9; y++)
            {
              result_A_temp[2] += analogRead(A2);
            }
            result_A[2] = result_A_temp[2]/10;

            if((result_A[0]+result_A[1]+result_A[2] - result_A[3])  >= threshold_accel || (result_A[0]+result_A[1]+result_A[2] - result_A[3])  <= -threshold_accel )
            {
              temp_mov = true;
            }
            result_A[3] = result_A[0]+result_A[1]+result_A[2];

            return temp_mov;

}

void display7Seg() {
            print_BCD(score);

}


int print_BCD(int number){





  

    int hundreds = 0;
    int tens = 0;
    int units = 0;

  if(number < 10){

    units = number % 10;

    for(int i = 0; i < 3 ; i++){

    if(i < 2){
      for(int y = 0; y < 7; y++){
        digitalWrite(*(ptr_pinout[i] + y), HIGH);
      }
    }
    else{

        for(int z = 0; z < 7; z++){
          digitalWrite(*(ptr_pinout[i] + z), (BCD[units][z]));
        }
     }

    }
  }
  else if(number < 100){

    tens = (number / 10) % 10;
    units = number % 10;


      for(int y = 0; y < 7; y++){
        digitalWrite(*(ptr_pinout[0] + y), HIGH);
      }




        for(int z = 0; z < 7; z++){
          digitalWrite(*(ptr_pinout[1] + z), BCD[tens][z]);
        }
 

              for(int z = 0; z < 7; z++){
          digitalWrite(*(ptr_pinout[2] + z), (BCD[units][z]));
        }
 

    }

  else if(number < 1000){

    hundreds = number / 100;
    tens = (number / 10) % 10;
    units = number % 10;
    

    
    
        for(int z = 0; z < 7; z++){
          //Serial.print("  val = "); Serial.print(*(ptr_pinout[0] + z),DEC); Serial.print("  z = "); Serial.print(z , DEC);Serial.print("  Hundreds = "); Serial.print(hundreds , DEC); Serial.print("\n\r");
          digitalWrite(*(ptr_pinout[0] + z), BCD[hundreds][z]);
        }
 

        for(int z = 0; z < 7; z++){
          //Serial.print("  val = "); Serial.print(*(ptr_pinout[1] + z),DEC); Serial.print("  z = "); Serial.print(z , DEC);Serial.print("  Tens = "); Serial.print(tens , DEC); Serial.print("\n\r");
          digitalWrite(*(ptr_pinout[1] + z), BCD[tens][z]);
        }
 



        for(int z = 0; z < 7; z++){
          //Serial.print("  val = "); Serial.print(((*(ptr_pinout[2])) + z),DEC); Serial.print("  z = "); Serial.print(z , DEC);Serial.print("  Units = "); Serial.print(units , DEC); Serial.print("\n\r");
          digitalWrite(*(ptr_pinout[2] + z), (BCD[units][z]));
        }
 


  }
  else{

    return -1;

  }

  return 1;

}