#include "DT130.hpp"

int DT130TEST::timerCounter = 1;
int DT130TEST::interruptCounter = 0;
int DT130TEST::pulseCountArray[3] = {800, 1000, 1450};
int DT130TEST::arrayItr = 0;

void DT130TEST::countTimer(){
if (timerCounter == 120){ // how many seconds until you want to call your real interrupt function
  timerCounter = 1;
  timerInterrupt();
} else {
  timerCounter++;
}
}

void DT130TEST::timerInterrupt(){
  arrayItr = (arrayItr == 2) ? 0 : arrayItr + 1;
  Serial.print("timerInterrupt, pcounts: ");
parentPayload->pcounts = pulseCountArray[arrayItr];
Serial.println(parentPayload->pcounts);
}


void DT130TEST::setCaliData(){
  for (int i = 0;i < 10; ++i){
    baseCaliData[i].height = i*469;
    baseCaliData[i].pcount = 770 + (78*i);
  }
} 


void DT130TEST::setTempADC(uint16_t ADCVal){
parentPayload->tempADC = ADCVal;
}

void DT130TEST::setTempOffset(uint8_t tempOffsetVal){
  parentPayload->tempOffset = tempOffsetVal;
}

void DT130TEST::setDielectric(uint16_t dielectricVal){
parentPayload->dielectric = dielectricVal;
}

void DT130TEST::setPulseCount(uint16_t pulseVal){
parentPayload->pcounts = pulseVal;
}

DT130TEST::DT130(){
  Serial.println("DT130 Test Created");
  setCaliData(); // sets calibration data on object creation
}

void DT130TEST::runTest(){
  Serial.println("Run Test : DT130 Test");
  setPulseCount(800);
    Timer1.initialize(1000000); // this timer does not behave. no matter what it triggers at like 8 seconds for some reason. have to come back
  Timer1.attachInterrupt(countTimer); // sets interrupt service routine
}