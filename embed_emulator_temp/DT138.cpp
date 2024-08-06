#include "DT138.hpp"


int Dt138Test::timerCounter = 1;
int Dt138Test::interruptCounter = 0;


void Dt138Test::setCaliData(){
  for (int i = 0;i < 10; ++i){
    baseCaliData[i].height = i*469;
    baseCaliData[i].pcount = 770 + (78*i);
  }
}


void Dt138Test::countTimer(){
if (timerCounter == 14){ // how many seconds until you want to call your real interrupt function
  timerCounter = 1;
  timerInterrupt();
} else {
  timerCounter++;
}
}

void Dt138Test::timerInterrupt(){
  if (interruptCounter < 2){
    interruptCounter++;
  } else {
    parentPayload->pcounts  = (parentPayload->pcounts > 1100) ? parentPayload->pcounts - 45 : 1400;
    interruptCounter = 0;
  }
}


Dt138Test::Dt138Test(){
Serial.println("DT138 Test Created");

}


void Dt138Test::runTest(){
    Serial.println("Run Test : DT138 Test");
    parentPayload->pcounts = 1400;
    Timer1.initialize(1000000); // this timer does not behave. no matter what it triggers at like 8 seconds for some reason. have to come back
  Timer1.attachInterrupt(countTimer); // sets interrupt service routine



}