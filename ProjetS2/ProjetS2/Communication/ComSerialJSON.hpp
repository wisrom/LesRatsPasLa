#pragma once

#include <string>
#include <iostream>

#include "include/serial/SerialPort.hpp"
#include "include/json.hpp"
#include "../Types/InputGame.hpp"
#include "../Types/InputMenu.hpp"

#define BAUD 256000
#define MSG_MAX_SIZE 1024
#define COM_DELAY_MS 20
#define ENCODER_SPEED_MULT 0.6f

class ComSerialJSON
{
public:
  ComSerialJSON();
  ~ComSerialJSON();

  void init();
  void comTest();
  InputGame getGameInput(int score);
  InputMenu getMenuInput();
  void sendGameData(int score);
private:
  SerialPort* arduino;
  float previousArduinoTime_ms;
  int lastScore;

  bool SendToSerial(SerialPort* arduino, nlohmann::json j_msg);
  bool RcvFromSerial(SerialPort* arduino, std::string& msg);
};