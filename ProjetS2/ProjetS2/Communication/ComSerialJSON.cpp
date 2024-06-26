#include "ComSerialJSON.hpp"

ComSerialJSON::ComSerialJSON()
{
  previousArduinoTime_ms = 0;
}

ComSerialJSON::~ComSerialJSON()
{
  delete arduino;
}

void ComSerialJSON::init()
{
  // Initialisation du port de communication
  std::string com;
  std::cout << "Entrer le port de communication du Arduino: ";
  std::cin >> com;
  arduino = new SerialPort(com.c_str(), BAUD);

  if (!arduino->isConnected()) 
  {
    std::cerr << "Impossible de se connecter au port " << std::string(com) << ". Fermeture du programme!" << std::endl;
    exit(1);
  }
}

InputGame ComSerialJSON::getGameInput()
{
  std::string raw_msg;
  nlohmann::json j_msg_send, j_msg_rcv;
  float arduinoTime_ms;

  InputGame input;
  input.hasPulled = false;
  input.menu = false;
  input.movement = { 0, 0 };
  input.quit = false;
  input.reelSpeed_rpm = 0.0f;

  j_msg_send["7Seg"] = 13;
  j_msg_send["LCD"] = "allo";
  j_msg_send["vib"] = int(3);
  if (!SendToSerial(arduino, j_msg_send)) 
  {
    std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
  }

  j_msg_rcv.clear();
  if (!RcvFromSerial(arduino, raw_msg))
  {
    std::cerr << "Erreur lors de la reception du message. " << std::endl; // UPDATE
  }

  if (raw_msg.size() > 0)
  {
    j_msg_rcv = nlohmann::json::parse(raw_msg);

    // Parse
    input.movement.x = (int)j_msg_rcv["joyx"];
    input.movement.y = (int)j_msg_rcv["joyy"];

    input.hasPulled = (bool)j_msg_rcv["mov"];
    
    input.reelSpeed_rpm = (float)j_msg_rcv["enc"];
    arduinoTime_ms = (float)j_msg_rcv["time"];
    //input.inputDuration_s = (arduinoTime_ms - previousArduinoTime_ms) + COM_DELAY_MS * 0.001;
    input.inputDuration_s = 1.0f;
  }

  Sleep(COM_DELAY_MS);

  return input;
}

void ComSerialJSON::sendGameData(int score)
{
  nlohmann::json j_msg_send;

  j_msg_send["7Seg"] = score;
  j_msg_send["LCD"] = "allo";
  j_msg_send["vib"] = int(3);

  if (!SendToSerial(arduino, j_msg_send))
  {
    std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
  }
}

void ComSerialJSON::comTest()
{
  std::string raw_msg;

  // Structure de donnees JSON pour envoie et reception
  int led_state = 1;
  nlohmann::json j_msg_send, j_msg_rcv;

  // Boucle pour tester la communication bidirectionnelle Arduino-PC
  for (int i = 0; i < 100; i++) 
  {
    // Envoie message Arduino
    j_msg_send["7Seg"] = i;
    j_msg_send["LCD"] = "allo";
    j_msg_send["vib"] = int(3);
    if (!SendToSerial(arduino, j_msg_send)) 
    {
      std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
    }
    // Reception message Arduino
    j_msg_rcv.clear(); // effacer le message precedent
    if (!RcvFromSerial(arduino, raw_msg)) 
    {
      std::cerr << "Erreur lors de la reception du message. " << std::endl;
    }

    // Impression du message de l'Arduino si valide
    if (raw_msg.size() > 0) 
    {
      j_msg_rcv = nlohmann::json::parse(raw_msg);
      std::cout << "Message de l'Arduino: " << j_msg_rcv << std::endl;
    }

    //Changement de l'etat led
    led_state = !led_state;

    // Bloquer le fil pour environ 1 sec
    Sleep(100);
  }
}

bool ComSerialJSON::SendToSerial(SerialPort* arduino, nlohmann::json j_msg)
{
  // Return 0 if error
  std::string msg = j_msg.dump();
  bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
  return true;
}

bool ComSerialJSON::RcvFromSerial(SerialPort* arduino, std::string& msg)
{
  // Return 0 if error
  // Message output in msg
  std::string str_buffer;
  char char_buffer[MSG_MAX_SIZE];
  int buffer_size;

  msg.clear(); // clear string

  // Version fonctionnelle dans VScode et Visual Studio
  buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
  str_buffer.assign(char_buffer, buffer_size);
  msg.append(str_buffer);

  return true;
}