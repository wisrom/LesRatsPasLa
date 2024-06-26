#pragma once

#include <string>
#include <iostream>

#include "include/serial/SerialPort.hpp"
#include "include/json.hpp"
#include "../Types/InputGame.hpp"

#define BAUD 256000
#define MSG_MAX_SIZE 1024
#define COM_DELAY_MS 50

class ComSerialJSON
{
public:
  ComSerialJSON();
  ~ComSerialJSON();

  void init();
  void comTest();
  InputGame getGameInput();
  void sendGameData(int score);
private:
  SerialPort* arduino;
  float previousArduinoTime_ms;

  bool SendToSerial(SerialPort* arduino, nlohmann::json j_msg);
  bool RcvFromSerial(SerialPort* arduino, std::string& msg);
};