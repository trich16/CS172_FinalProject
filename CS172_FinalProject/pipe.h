#ifndef PIPE_H
#define PIPE_H

class Pipe
{
  private:
    int pinNumber;
    long waterFreq;
    long prevFreq;
    long waterLength;
    long prevLength;
    int pumpSet;
    int tempPin;
    int humPin;
  public:
    void setPinNumber(int i);
    int getPinNumber();
    void turnOn();
    void turnOff();
    void setWaterFreq(int i);
    int getWaterFreq();
    void setWaterLength(int i);
    void checkFreq();
    void setPumpSet();
    int getPumpSet();
    void setTempPin(int i);
    int getTempPin();
    void setHumPin(int i);
    int getHumPin();
    //need constructor
    void setPrevFreq(int i);
};

#endif
