#pragma once
#include <TimerOne.h>
#include "Wire2.h"
#include "Structs.hpp"
#include "ParentTest.hpp"

/*
test iterates over a normal level, low level, and high level pulse count on repeat
*/

class DT130TEST : public ParentTest {
  private:
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function
static int interruptCounter; //used to see how many times the interrupt function has been called
static int pulseCountArray[3];
static int arrayItr;

static void countTimer();

static void timerInterrupt();


void setCaliData() override; // sets some basic calibration data

// all these functions just set some basic values to the payload object
void setTempADC(uint16_t ADCVal);

void setTempOffset(uint8_t tempOffsetVal);

void setDielectric(uint16_t dielectricVal);

void setPulseCount(uint16_t pulseVal);


public:

DT130(); // constructor

void runTest() override; // starts running the test
};



