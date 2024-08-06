#include "BC1Test.hpp"

int BC1::timerCounter = 1;
int BC1::interruptCounter = 0;
int BC1::values[10] = {675,749,817,888,958,1024,1093,1164,1232,1265};
int BC1::valuesItr = 0;



void BC1::setCaliData(){
baseCaliData[0].height = 0;
baseCaliData[0].pcount = 675;

baseCaliData[1].height = 469;
baseCaliData[1].pcount = 742;

baseCaliData[2].height = 938;
baseCaliData[2].pcount = 811;

baseCaliData[3].height = 1406;
baseCaliData[3].pcount = 881;

baseCaliData[4].height = 1875;
baseCaliData[4].pcount = 952;

baseCaliData[5].height = 2344;
baseCaliData[5].pcount = 1020;

baseCaliData[6].height = 2813;
baseCaliData[6].pcount = 1090;

baseCaliData[7].height = 3281;
baseCaliData[7].pcount = 1159;

baseCaliData[8].height = 3750;
baseCaliData[8].pcount = 1229;

baseCaliData[9].height = 4180;
baseCaliData[9].pcount = 1312;

}


void BC1::countTimer(){
if (timerCounter == 30){ // how many seconds until you want to call your real interrupt function
  timerCounter = 1;
  timerInterrupt();
} else {
  timerCounter++;
}
}

void BC1::timerInterrupt(){
parentPayload->pcounts = values[valuesItr];
valuesItr = (valuesItr < 9) ? valuesItr + 1 : 0;
}


BC1::BC1(){
Serial.println("BC1 Test Created");

}


void BC1::runTest(){
    Serial.println("Run Test : BC1 Test");
    parentPayload->pcounts = 1000;
    parentPayload->dielectric = 2500;
    parentPayload->tempOffset = -13;
    parentPayload->tempADC = 851;
    Timer1.initialize(1000000); // this timer does not behave. no matter what it triggers at like 8 seconds for some reason. have to come back
  Timer1.attachInterrupt(countTimer); // sets interrupt service routine



}