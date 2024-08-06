#include "DT142.hpp"

int Dt142Test::timerCounter = 1;
int Dt142Test::interruptCounter = 0;
int Dt142Test::invalidValues[15] = {0,400, 600, 700, 1600, 1700, 1800, 1900, 2000, -100, -1000,-10000,20000, 30000, 60000};
int Dt142Test::invalidItr = 0;

void Dt142Test::setCaliData(){
  for (int i = 0;i < 10; ++i){
    baseCaliData[i].height = i*469;
    baseCaliData[i].pcount = 770 + (78*i);
  }
}


void Dt142Test::countTimer(){
if (timerCounter == 30){ // how many seconds until you want to call your real interrupt function
  timerCounter = 1;
  timerInterrupt();
} else {
  timerCounter++;
}
}

void Dt142Test::timerInterrupt(){
parentPayload->pcounts = invalidValues[invalidItr];
invalidItr = (invalidItr < 14) ? invalidItr + 1 : 0;
}


Dt142Test::Dt142Test(){
Serial.println("DT138 Test Created");

}


void Dt142Test::runTest(){
    Serial.println("Run Test : DT142 Test");
    parentPayload->pcounts = 1000;
    Timer1.initialize(1000000); // this timer does not behave. no matter what it triggers at like 8 seconds for some reason. have to come back
  Timer1.attachInterrupt(countTimer); // sets interrupt service routine



}