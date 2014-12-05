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
    char humPin;
  public:
    Pipe pipe();
    void setPinNumbers(int i, char j);
    int getPinNumber();
    void turnOn();
    void turnOff();
    void setWaterFreq(int i);
    int getWaterFreq();
    void setWaterLength(int i);
    int getWaterLength();
    void checkFreq();
    void setPumpSet();
    int getPumpSet();
    void setTempPin(int i);
    int getTempPin();
    void setHumPin(int i);
    char getHumPin();
    //need constructor
    void setPrevFreq(int i);
};

#endif
