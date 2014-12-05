
#include <SD.h>
//#include <Ethernet.h>
//#include "Twitter.h"
#include "pipe.h"
//#include "waterTime.txt"
File dataFile;
const int numberOfPipes = 3;
int pumpPin = 5;
int pumpStat = 0;
int sensorFreq = 5000;
int sensorLast = 0;
//create three pipe objects 
long int txtNumber[6];
Pipe pipe[3];
//DEFAULT CONSTRUCTOR


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
    
    pipe[0].setWaterFreq(6000);
    pipe[1].setWaterFreq(6000);
    pipe[2].setWaterFreq(6000);
    
    pipe[0].setWaterLength(5000);
    pipe[1].setWaterLength(5000);
    pipe[2].setWaterLength(5000);
    
  //initialize pins to output
  for (int i = 0; i < numberOfPipes; i++) 
    pinMode(pipe[i].getPinNumber(), OUTPUT);
    
  
  
  
  dataFile = SD.open("test.txt", FILE_READ);
  if (SD.exists("test.txt")) {
    Serial.print("Opening test.txt...");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
    if (SD.exists("test.txt")){
     Serial.println("Succeeded in opening test.txt");
  for(int i = 0; i < 6; i++){
     char c = dataFile.read();
     long int a;
     a=c-'0';
     txtNumber[i] = a *1000;
     Serial.println(txtNumber[i]); //output the variable on the screen to verify
    }
   }
  else
  {
    Serial.println ("couldn't read file");
  }
  dataFile.close();

  for(int i = 0; i < 3; i++){
    int f = txtNumber[i+i];
    int l = txtNumber[i+i+1];
    pipe[i].setWaterFreq(f);
    pipe[i].setWaterLength(l);
    Serial.println(pipe[i].getWaterLength()); 
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
  
  sensorCheck();
}

void sensorCheck(){
  
 unsigned long _currentMillis = millis();
  
  if(_currentMillis - sensorLast > sensorFreq){
    //save last time we collected data
    sensorLast = _currentMillis;
    int a;
    
      dataFile = SD.open("TOP_PIPE_SOIL_HUM.txt", FILE_WRITE);
      a = analogRead(pipe[0].getHumPin());
      dataFile.println(a);
      Serial.println(a);
      dataFile.close();
    
      dataFile = SD.open("midPipeSoilHum.txt", FILE_WRITE);
      a = analogRead(pipe[1].getHumPin());
      dataFile.println(a);
      Serial.println(a);
      dataFile.close();
    
      dataFile = SD.open("botPipeSoilHum.txt", FILE_WRITE);
      a = analogRead(pipe[2].getHumPin());
      dataFile.println(a);
      Serial.println(a);
      dataFile.close();
  }
}
