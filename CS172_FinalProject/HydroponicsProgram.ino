#include <SD.h>
//#include <Ethernet.h>
//#include "Twitter.h"
#include "pipe.h"
//#include "waterTime.txt"
File dataFile;
const int numberOfPipes = 3;
int pumpPin = 5;
int pumpStat = 0;
//create three pipe objects 
Pipe pipe[3];

//DEFAULT CONSTRUCTOR
//Pipe::Pipe ()
//{
 //pumpSet = 0;
 //pinMode(pinNumber, OUTPUT);
//} 

void setup()
{
  //open serial communication, initialize SD card
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  pinMode(10, OUTPUT);
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  else
    Serial.println("initialization done.");
    
  //set arduino pin numbers for each pipe
    pipe[0].setPinNumber(2);
    pipe[1].setPinNumber(3);
    pipe[2].setPinNumber(5);
    
    pipe[0].setWaterFreq(10000);
    pipe[1].setWaterFreq(10000);
    pipe[2].setWaterFreq(10000);
    
    pipe[0].setWaterLength(5000);
    pipe[1].setWaterLength(5000);
    pipe[2].setWaterLength(5000);
    
    pipe[0].setPrevFreq(0);
    pipe[1].setPrevFreq(0);
    pipe[2].setPrevFreq(0);
    
    pipe[0].setPumpSet();
    pipe[1].setPumpSet();
    pipe[2].setPumpSet();
  
  //initialize pins to output
  for (int i = 0; i < numberOfPipes; i++) 
    pinMode(pipe[i].getPinNumber(), OUTPUT);
    
  
  
  
  dataFile = SD.open("test.txt", FILE_WRITE);
  dataFile.close();
  if (SD.exists("test.txt")) {
    Serial.print("Writing to test.txt...");
    dataFile = SD.open("test.txt", FILE_WRITE);
    dataFile.println("this is awesomely awesome!");
    // close the file:
    dataFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  
}

void loop()
{
  //loop checks whether it is time to water or not. If it is, it waters for the correct length.
  for (int i=0; i < numberOfPipes; i++){
    pipe[i].checkFreq();
  }
  
  
  if(pipe[0].getPumpSet() == 1 || pipe[1].getPumpSet() == 1 || pipe[2].getPumpSet() == 1){
    if(pumpStat == 0){
      Serial.print("Pump Turned On at: ");
      Serial.print(millis() / 1000);
      Serial.println(" seconds");
    }
    pumpStat = 1;
    //digitalWrite(pumpPin, HIGH);
  }
  else{
    if(pumpStat == 1){
      Serial.print("Pump Turned Off at: ");
      Serial.print(millis() / 1000);
      Serial.println(" seconds");
    }
    pumpStat = 0;
    //digitalWrite(pumpPin, LOW);
  }
}
