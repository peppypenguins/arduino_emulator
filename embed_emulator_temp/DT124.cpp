#include "DT124.hpp"


int Dt124Test::timerCounter = 1;
int Dt124Test::interruptCounter = 0;


void Dt124Test::setCaliData(){
  for (int i = 0;i < 10; ++i){
    baseCaliData[i].height = i*469;
    baseCaliData[i].pcount = 770 + (78*i);
  }
}


void Dt124Test::countTimer(){
if (timerCounter == 20){ // how many seconds until you want to call your real interrupt function
  timerCounter = 1;
  timerInterrupt();
} else {
  timerCounter++;
}
}

void Dt124Test::timerInterrupt(){
    parentPayload->pcounts  = (parentPayload->pcounts < 1400) ? parentPayload->pcounts + 50 : 800;
}


Dt124Test::Dt124Test(){
Serial.println("DT124 Test Created");

}

void Dt124Test::runTest(){
    Serial.println("Run Test : DT124 Test");
    parentPayload->pcounts = 800;
    Timer1.initialize(1000000); // this timer does not behave. no matter what it triggers at like 8 seconds for some reason. have to come back
  Timer1.attachInterrupt(countTimer); // sets interrupt service routine
}