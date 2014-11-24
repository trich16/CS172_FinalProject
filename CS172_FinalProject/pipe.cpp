#include "pipe.h"

void Pipe::setPinNumber(int i)
{
  pinNumber = i;
}

int Pipe::getPinNumber()
{
  return pinNumber;  
}

void Pipe::turnOn()
{
  digitalWrite(pinNumber, HIGH);
}

void Pipe::turnOff(String p)
{
  digitalWrite(pinNumber, LOW);
}


