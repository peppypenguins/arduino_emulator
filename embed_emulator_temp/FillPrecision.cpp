#include "FillPrecision.hpp"

int FillPrecision::timerCounter = 1;

void FillPrecision::setCaliData(){
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


void FillPrecision::countTimer(){
timerInterrupt();
}

void FillPrecision::timerInterrupt(){
if (parentPayload->samplingMode == 2 || parentPayload->samplingMode == 1){
  parentPayload->pcounts = 1000;
} else {
  parentPayload->pcounts = 900;
}
}


FillPrecision::FillPrecision(){
Serial.println("FillPrecision Test Created");

}


void FillPrecision::runTest(){
    Serial.println("Run Test : FillPrecision Test");
    parentPayload->pcounts = 900;
    parentPayload->dielectric = 1710;
    parentPayload->tempOffset = -16;
    parentPayload->tempADC = 855;
    Timer1.initialize(500000); // this timer does not behave. no matter what it triggers at like 8 seconds for some reason. have to come back
  Timer1.attachInterrupt(countTimer); // sets interrupt service routine
}