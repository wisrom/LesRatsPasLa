#pragma once

#include <string>
#include <iostream>

#include "include/serial/SerialPort.hpp"
#include "include/json.hpp"

#define BAUD 256000
#define MSG_MAX_SIZE 1024

class ComSerialJSON
{
public:
  ComSerialJSON();
  ~ComSerialJSON();

  void comTest();
private:
  SerialPort* arduino;

  bool SendToSerial(SerialPort* arduino, nlohmann::json j_msg);
  bool RcvFromSerial(SerialPort* arduino, std::string& msg);
};