#include "DT145.hpp"


int Dt145Test::timerCounter = 1;
int Dt145Test::interruptCounter = 0;


void Dt145Test::setCaliData(){
  for (int i = 0;i < 10; ++i){
    baseCaliData[i].height = i*469;
    baseCaliData[i].pcount = 770 + (78*i);
  }
}


void Dt145Test::countTimer(){
if (timerCounter == 10){ // how many seconds until you want to call your real interrupt function
  timerCounter = 1;
  timerInterrupt();
} else {
  timerCounter++;
}
}

void Dt145Test::timerInterrupt(){
  if (interruptCounter < 2){
    interruptCounter++;
  } else {
    parentPayload->pcounts  = (parentPayload->pcounts < 1400) ? parentPayload->pcounts + 30 : 1400;
    interruptCounter = 0;
  }
}


Dt145Test::Dt145Test(){
Serial.println("DT145 Test Created");

}


void Dt145Test::runTest(){
    Serial.println("Run Test : DT145 Test");
    parentPayload->pcounts = 900;
    Timer1.initialize(1000000); // this timer does not behave. no matter what it triggers at like 8 seconds for some reason. have to come back
  Timer1.attachInterrupt(countTimer); // sets interrupt service routine



}