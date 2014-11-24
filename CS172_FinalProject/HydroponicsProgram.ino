#include <SD.h>
#include <Ethernet.h>
#include "Twitter.h"
#include "pipe.h"
#include "waterTime.txt"

const int numberOfPipes = 3;
Pipe pipe[numberOfPipes] {lowPipe, midPipe, highPipe};

void setup
{
  for (int i = 0; i < numberOfPipes; i++) 
    pinMode(pipe[i], OUTPUT);
}

