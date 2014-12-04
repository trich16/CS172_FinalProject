
#include <SD.h>
#include <Ethernet.h>
//#include "Twitter.h"
#include "pipe.h"
#include <SPI.h>
#include <Ethernet.h>
//#include "sha1.h"
#include "Time.h"
#include <EEPROM.h>

File dataFile;
const int numberOfPipes = 3;
int pumpPin = 5;
int pumpStat = 0;
char txtNumber[6];
//create three pipe objects 
Pipe pipe[3];

void setup()
{
  //open serial communication, initialize SD card
  Serial.begin(9600);                             // We may need to change this to 115200 due to Twitter if it is slow
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
    
  
  
  dataFile = SD.open("test.txt", FILE_READ);
  if (SD.exists("test.txt")) {
    Serial.print("Writing to test.txt...");
    //dataFile = SD.open("hydroponics.txt", FILE_WRITE);
    //dataFile.println("this is awesomely awesome!");
    // close the file:
    //dataFile.close();
    //Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  //make a read function to return the numbers we need
  if (SD.exists("test.txt")){
     Serial.print("Success!");
     
  for(int i = 0; i < 6; i++){
     char c = dataFile.read(); 
     txtNumber[i] = c; 
     Serial.print(txtNumber[i]);
    }
   }
  else
  {
    Serial.println ("couldn't read file");
  }
  dataFile.close();
  
  for(int i = 0; i < 3; i++){
    pipe[i].setWaterFreq(txtNumber[i+i]);
    pipe[i].setWaterLength(txtNumber[i+i+1]); 
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
