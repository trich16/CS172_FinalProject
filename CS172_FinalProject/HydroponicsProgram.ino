#include <SD.h>
#include "pipe.h"
File dataFile;
const int numberOfPipes = 3;
int pumpPin = 5;
int pumpStat = 0;

//how often you want the program to read sensors in milliseconds 
int sensorFreq = 5000;
long int sensorLast = 0;
//create three pipe objects 
long int txtNumber[6];
Pipe pipe[3];


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
    pipe[0].setPinNumbers(2, A0);
    pipe[1].setPinNumbers(3, A1);
    pipe[2].setPinNumbers(5, A2);

  //initialize pins to output
  for (int i = 0; i < numberOfPipes; i++) 
    pinMode(pipe[i].getPinNumber(), OUTPUT);
    
  //Open the text file containing input data from the sd card
  dataFile = SD.open("test.txt", FILE_READ);
  if (SD.exists("test.txt")) {
    Serial.print("Opening test.txt...");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  //take char inputs from the txt file, turn them into ints, and store them in an array.
    if (SD.exists("test.txt")){
     Serial.println("Succeeded in opening test.txt");
  for(int i = 0; i < 6; i++){
     char c = dataFile.read();
     long int a;
     a=c-'0';
     txtNumber[i] = a *60000; // multiply by 60000 to change the values from milliseconds to minutes
     Serial.println(txtNumber[i]); //output the variable on the screen to verify
    }
   }
  else
  {
    Serial.println ("couldn't read file");
  }
  dataFile.close();

  // set the frequency and and length of the water times from the txtNumber array
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
   // Serial.println(pipe[i].getWaterFreq());
  }
  
  // checks to see if any pipes needs the pump to be on and turns the pump on or off accordingly
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
  
  //calls sensorCheck function 
  sensorCheck();
}


//function checks if it is time to read sensors and print values to files
void sensorCheck(){
  //millis() continuously checks the time since the program began running
 unsigned long _currentMillis = millis();
 
  //if statement evaluates whether the correct time between sensor reads has elapsed
  if(_currentMillis - sensorLast > sensorFreq){
    //save last time we collected data
    sensorLast = _currentMillis;
    int a;
    
    //opens bottom pipe humidity data file to write
      dataFile = SD.open("0hum.txt", FILE_WRITE);
      if (dataFile) {
      //reads the current sensor voltage and prints to the file
        a = analogRead(pipe[0].getHumPin());
        dataFile.println(a);
        Serial.println(a);
        dataFile.close();
      }
      else{
        Serial.println("error opening 0hum.txt.");
      }
    
    //opens middle pipe humidity data file to write
      dataFile = SD.open("1hum.txt", FILE_WRITE);
      if (dataFile) {
      //reads current sensor voltage and prints to file
        a = analogRead(pipe[1].getHumPin());
        dataFile.println(a);
        Serial.println(a);
        dataFile.close();
      }
      else{
        Serial.println("error opening 1hum.txt.");
      }
      
      //opens top pipe humidity data file to write
      dataFile = SD.open("2hum.txt", FILE_WRITE);
      if (dataFile){
      //reads current sensor voltage and prints to file
        a = analogRead(pipe[2].getHumPin());
        dataFile.println(a);
        Serial.println(a);
        dataFile.close();
      }
      else{
        Serial.println("error opening 3hum.txt.");
      }
  }
}
