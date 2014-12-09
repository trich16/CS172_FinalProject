#include "pipe.h"
#include "Arduino.h"

void Pipe::setWaterFreq(int i)
{
  waterFreq = i;
}

int Pipe::getWaterFreq()
{
  return waterFreq;
}

void Pipe::setWaterLength(int i)
{
  waterLength = i;
}

int Pipe::getWaterLength()
{
  return waterLength;
}

//hum pin is an analog pin which must be a char
void Pipe::setPinNumbers(int i, char j)
{
  pinNumber = i; //set the pin number for output on the microcontroller
  humPin = j;    //set the pin number for input of the humidity sensor data
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

char Pipe::getHumPin()
{
  return humPin;
}

void Pipe::turnOn()
{
  digitalWrite(pinNumber, HIGH); //set the voltage output to 5 to turn on the flow of water
}

void Pipe::turnOff()
{
  digitalWrite(pinNumber, LOW); //set the voltage output to 0 to turn off the flow of water
}

void Pipe::checkFreq()
{
  unsigned long currentMillis = millis();
  //if statement evaluates whether the right amount of time has passed to water.
  if(currentMillis - prevFreq > waterFreq){
    //save last time we watered
    prevFreq = currentMillis;
    //turn on watering
    //pumpset variable allows us to only call this if statement once before the other if statement must be called
    //making it so it will only print once, not continuously.
    if (pumpSet == 0){
       Serial.print(pinNumber); 
       Serial.print(" Turned On at: ");
       Serial.print(currentMillis / 1000);
       Serial.println(" seconds");
       } 
    pumpSet = 1;
    turnOn();
    }
  
  //if statement evaluates if the right watering length has elapsed yet.
  //if it has, this code will turn off the watering.
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

void Pipe::setPumpSet()
{
  pumpSet = 0;
}

//pipe class constructor
Pipe Pipe::pipe()
{
 pumpSet = 0;
 prevFreq = 0;
}

    
    
