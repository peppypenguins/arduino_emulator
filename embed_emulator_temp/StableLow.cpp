#include "StableLow.hpp"



void StableLow::setCaliData(){
  for (int i = 0;i < 10; ++i){
    baseCaliData[i].height = i*469;
    baseCaliData[i].pcount = 800 + (78*i);
  }
}


StableLow::StableLow(){
  Serial.println("StableLow Test Created");
  setCaliData(); // sets calibration data on object creation
}



void StableLow::setTempADC(uint16_t ADCVal){
parentPayload->tempADC = ADCVal;
}

void StableLow::setTempOffset(uint8_t tempOffsetVal){
parentPayload->tempOffset = tempOffsetVal;
}

void StableLow::setDielectric(uint16_t dielectricVal){
parentPayload->dielectric = dielectricVal;
}

void StableLow::setPulseCount(uint16_t pulseVal){
parentPayload->pcounts = pulseVal;
}

void StableLow::runTest(){
  setTempADC(860);
setTempOffset(0);
setDielectric(1710);
setPulseCount(800);
}