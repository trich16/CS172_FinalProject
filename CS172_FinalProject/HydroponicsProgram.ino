#include <SD.h>
#include <Ethernet.h>
#include "Twitter.h"
#include "pipe.h"
#include "waterTime.txt"

const int numberOfPipes = 3;


void setup
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

  //create three pipe objects 
  Pipe pipe[numberOfPipes] {topPipe, midPipe, botPipe};
  
  //set arduino pin numbers for each pipe
  topPipe.setPinNumber(2);
  midPipe.setPinNumber(3);
  botPipe.setPinNumber(5);
  
  //initialize pins to output
  for (int i = 0; i < numberOfPipes; i++) 
    pinMode(pipe[i].getPinNumber(), OUTPUT);
    
  //opens waterTime file if it exists
  if (SD.exists("waterTime.txt")){
    SD.open("waterTime.txt", FILE_READ);
  }
  else {
    Serial.println("Could not open waterTime.txt");
    }  
  
  
}

void loop
{
  
}

