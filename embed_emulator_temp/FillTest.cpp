
#include "FillTest.hpp"

int FillTest::timerCounter = 1;
int FillTest::interruptCounter = 0;


void FillTest::setCaliData(){
  for (int i = 0;i < 10; ++i){
    baseCaliData[i].height = i*469;
    baseCaliData[i].pcount = 770 + (78*i);
  }
}


void FillTest::countTimer(){
if (timerCounter == 10){ // how many seconds until you want to call your real interrupt function
  timerCounter = 1;
  timerInterrupt();
} else {
  timerCounter++;
}
}


void FillTest::timerInterrupt(){
  if (interruptCounter < 6){
    interruptCounter++;
} else if (interruptCounter < 12){
parentPayload->pcounts += 65;
interruptCounter++;
} else if (interruptCounter < 60){
interruptCounter++;
} else {
  parentPayload->pcounts = 900;
  interruptCounter = 0;
}

}

FillTest::FillTest(){
  Serial.println("Fill Test Created");
}

void FillTest::runTest(){
    Serial.println("Run Test : Fill Test");
    parentPayload->pcounts = 900;
    Timer1.initialize(1000000); // Timer can't be much bigger or else it will overflow and break, currently set to 1 second
  Timer1.attachInterrupt(countTimer); // sets interrupt service routine

}