
#include "IncrementTest.hpp"

int IncrementTest::timerCounter = 1;

void IncrementTest::countTimer(){
if (timerCounter == 20){ // how many seconds until you want to call your real interrupt function
  timerCounter = 1;
  timerInterrupt();
} else {
  timerCounter++;
}
}


void IncrementTest::setCaliData() { // sets some typical calibration data
  for (int i = 0;i < 10; ++i){
    baseCaliData[i].height = i*469;
    baseCaliData[i].pcount = 770 + (78*i);
  }
}

 void IncrementTest::timerInterrupt(){ // has pulse counts loop from 800-1500
  Serial.print("timer pCounts: 0x");
  Serial.println(parentPayload->pcounts);
 if (parentPayload->pcounts < 1500){
  parentPayload->pcounts += 100;
} else {
  parentPayload->pcounts = 800;
}
}

IncrementTest::IncrementTest(){
  Serial.println("Increment Test Created");
  setCaliData(); // sets cali data on object creation
}

 void IncrementTest::runTest() {
  Serial.println("Run Test : Increment Test");
    Timer1.initialize(1000000);
  Timer1.attachInterrupt(countTimer); // attaches interrupt function
}
