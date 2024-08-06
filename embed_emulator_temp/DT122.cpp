#include "DT122.hpp"

int Dt122Test::timerCounter = 1;

void Dt122Test::setCaliData(){
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


void Dt122Test::countTimer(){
if (timerCounter == 60){ // how many seconds until you want to call your real interrupt function
  timerCounter = 1;
  timerInterrupt();
} else {
  timerCounter++;
}
}

void Dt122Test::timerInterrupt(){
parentPayload->newCRC = !parentPayload->newCRC;
Serial.print("update boolean :"); 
Serial.println(parentPayload->newCRC);
}


Dt122Test::Dt122Test(){
Serial.println("DT122 Test Created");

}


void Dt122Test::runTest(){
    Serial.println("Run Test : Dt122Test Test");
    parentPayload->pcounts = 900;
    parentPayload->dielectric = 1710;
    parentPayload->tempOffset = -16;
    parentPayload->tempADC = 855;
    Timer1.initialize(1000000); // this timer does not behave. no matter what it triggers at like 8 seconds for some reason. have to come back
  Timer1.attachInterrupt(countTimer); // sets interrupt service routine
}