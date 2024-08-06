
#include "ParentTest.hpp"

Payload* ParentTest::parentPayload = nullptr;


void ParentTest::setCaliData(){ // base function to set calibration data but should be implemented in child class
for (int i = 0; i < 10; ++i){
  baseCaliData[i].height = i * 100;
  baseCaliData[i].pcount = i * 200;
}
}





void ParentTest::setPayload(Payload* payloadSetup){ // sets the payload to whatever the given pointer is
parentPayload = payloadSetup;
}

void ParentTest::caliInit(){ // initalizes the calibration data in the payload to whatever the test has its cali data as 
delay(20);
for (int i = 0;i < 10; ++i){
  parentPayload->caliData[i] = baseCaliData[i];
 /* Serial.print("BaseCaliPair #");
  Serial.print(i);
  Serial.print(":");
  Serial.print(baseCaliData[i].height);
  Serial.print(",");
  Serial.println(baseCaliData[i].pcount);*/
}
 }

void ParentTest::runTest(){ // should never be run really. virtual function that child classes should implement

}
