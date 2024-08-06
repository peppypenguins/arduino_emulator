#include "BC2Test.hpp"

int BC2::timerCounter = 1;
int BC2::interruptCounter = 0;
int BC2::values[20] = {683,683,708,749,757,768,830,834,845,849,859,870,885,896,905,922,927,926,926,925};
int BC2::tempValues[20] = {855,855,857,857,857,857,859,859,862,863,859,863,867,867,866,866,866,863,863,863};
int BC2::valuesItr = 0;



void BC2::setCaliData(){
baseCaliData[0].height = 0;
baseCaliData[0].pcount = 672;

baseCaliData[1].height = 470;
baseCaliData[1].pcount = 738;

baseCaliData[2].height = 940;
baseCaliData[2].pcount = 815;

baseCaliData[3].height = 1410;
baseCaliData[3].pcount = 891;

baseCaliData[4].height = 1880;
baseCaliData[4].pcount = 966;

baseCaliData[5].height = 2350;
baseCaliData[5].pcount = 1038;

baseCaliData[6].height = 2820;
baseCaliData[6].pcount = 1111;

baseCaliData[7].height = 3290;
baseCaliData[7].pcount = 1185;

baseCaliData[8].height = 3760;
baseCaliData[8].pcount = 1257;

baseCaliData[9].height = 4180;
baseCaliData[9].pcount = 1310;
}


void BC2::countTimer(){
if (timerCounter == 30){ // how many seconds until you want to call your real interrupt function
  timerCounter = 1;
  timerInterrupt();
} else {
  timerCounter++;
}
}

void BC2::timerInterrupt(){
parentPayload->pcounts = values[valuesItr];
parentPayload->tempADC = tempValues[valuesItr];
valuesItr = (valuesItr < 19) ? valuesItr + 1 : valuesItr;
}


BC2::BC2(){
Serial.println("BC2 Test Created");

}


void BC2::runTest(){
    Serial.println("Run Test : BC2 Test");
    parentPayload->pcounts = 683;
    parentPayload->dielectric = 1710;
    parentPayload->tempOffset = -16;
    parentPayload->tempADC = 855;
    Timer1.initialize(1000000); // this timer does not behave. no matter what it triggers at like 8 seconds for some reason. have to come back
  Timer1.attachInterrupt(countTimer); // sets interrupt service routine
}