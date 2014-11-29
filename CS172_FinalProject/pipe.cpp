#include "pipe.h"
#include "Arduino.h"


void Pipe::setWaterFreq(int i)
{
  waterFreq = i;
}

void Pipe::setWaterLength(int i)
{
  waterLength = i;
}

void Pipe::setPinNumber(int i)
{
  pinNumber = i;
}

int Pipe::getPinNumber()
{
  return pinNumber;  
}

void Pipe::setTempPin(int i)
{
  tempPin = i;
}

int Pipe::getTempPin()
{
  return tempPin;
}

void Pipe::setHumPin(int i)
{
  humPin = i;
}

int Pipe::getHumPin()
{
  return humPin;
}

void Pipe::turnOn()
{
  digitalWrite(pinNumber, HIGH);
}

void Pipe::turnOff()
{
  digitalWrite(pinNumber, LOW);
}

void Pipe::checkFreq()
{
  unsigned long currentMillis = millis();
  
  if(currentMillis - prevFreq > waterFreq){
    //save last time we watered
    prevFreq = currentMillis;
    //turn on watering
    if (pumpSet == 0){
       Serial.print(pinNumber); 
       Serial.print(" Turned On at: ");
       Serial.print(currentMillis / 1000);
       Serial.println(" seconds");
       } 
    pumpSet = 1;
    turnOn();
    }
  
  if(currentMillis - prevFreq > waterLength){
    if(pumpSet == 1){
      Serial.print(pinNumber);
      Serial.print(" Turned Off at: ");
      Serial.print(currentMillis / 1000);
      Serial.println(" seconds");
      pumpSet = 0;
      }
    turnOff();
    }
}
  
int Pipe::getPumpSet()
{
  return pumpSet;
}

//need constructor
void Pipe::setPrevFreq(int i)
{
  prevFreq = i;
}

void Pipe::setPumpSet()
{
  pumpSet = 0;
}


    
    

