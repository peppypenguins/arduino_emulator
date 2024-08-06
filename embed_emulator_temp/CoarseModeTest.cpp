

#include "CoarseModeTest.hpp"


int CoarseModeTest::timerCounter = 1;
int CoarseModeTest::interruptCounter = 0;

void CoarseModeTest::countTimer(){
if (timerCounter == 30){ // how many seconds until you want to call your real interrupt function
  timerCounter = 1;
  timerInterrupt();
} else {
  timerCounter++;
}
}


void CoarseModeTest::timerInterrupt(){ // timer interrupt to simulate coarse mode
parentPayload->pcounts = (parentPayload->pcounts < 799) ? parentPayload->pcounts + 100 : 800;
}

void CoarseModeTest::setCaliData() { // sets some basic calibration data
//Serial.println("setCali");
  for (int i = 0;i < 10; ++i){
    baseCaliData[i].height = i*469;
    baseCaliData[i].pcount = 650 + (72*i);
  }
}


CoarseModeTest::CourseModeTest(){
  Serial.println("CourseMode Test Created");
  setCaliData(); // sets calibration data on object creation
}


 void CoarseModeTest::runTest() {
  Serial.println("Run Test : CourseMode Test");
  parentPayload->pcounts = 660;
  parentPayload->dielectric = 1710;
    Timer1.initialize(1000000); // this timer does not behave. no matter what it triggers at like 8 seconds for some reason. have to come back
  Timer1.attachInterrupt(countTimer); // sets interrupt service routine
}


