#include "StableHigh.hpp"



void StableHigh::setCaliData(){
  for (int i = 0;i < 10; ++i){
    baseCaliData[i].height = i*469;
    baseCaliData[i].pcount = 800 + (78*i);
  }
}


StableHigh::StableHigh(){
  Serial.println("StableHigh Test Created");
  setCaliData(); // sets calibration data on object creation
}



void StableHigh::setTempADC(uint16_t ADCVal){
parentPayload->tempADC = ADCVal;
}

void StableHigh::setTempOffset(uint8_t tempOffsetVal){
parentPayload->tempOffset = tempOffsetVal;
}

void StableHigh::setDielectric(uint16_t dielectricVal){
parentPayload->dielectric = dielectricVal;
}

void StableHigh::setPulseCount(uint16_t pulseVal){
parentPayload->pcounts = pulseVal;
}

void StableHigh::runTest(){
  setTempADC(860);
setTempOffset(0);
setDielectric(1710);
setPulseCount(1400);
}