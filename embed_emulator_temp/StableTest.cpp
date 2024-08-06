#include "StableTest.hpp"



void StableTest::setCaliData(){
  for (int i = 0;i < 10; ++i){
    baseCaliData[i].height = i*469;
    baseCaliData[i].pcount = 800 + (78*i);
  }
}


StableTest::StableTest(){
  Serial.println("StableTest Test Created");
  setCaliData(); // sets calibration data on object creation
}



void StableTest::setTempADC(uint16_t ADCVal){
parentPayload->tempADC = ADCVal;
}

void StableTest::setTempOffset(uint8_t tempOffsetVal){
parentPayload->tempOffset = tempOffsetVal;
}

void StableTest::setDielectric(uint16_t dielectricVal){
parentPayload->dielectric = dielectricVal;
}

void StableTest::setPulseCount(uint16_t pulseVal){
parentPayload->pcounts = pulseVal;
}

void StableTest::runTest(){
  setTempADC(860);
setTempOffset(0);
setDielectric(1710);
setPulseCount(1000);
}