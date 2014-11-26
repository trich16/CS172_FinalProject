#ifndef PIPE_H
#define PIPE_H

#include <String>

class Pipe
{
  private:
    int pinNumber;
    double waterFreq
    double waterLength
    string tempPin;
    string humPin;
  public:
    void setPinNumber(int i);
    int getPinNumber();
    void turnOn();
    void turnOff();
    void setWaterTime();
    void getWaterTime();
};

#endif
