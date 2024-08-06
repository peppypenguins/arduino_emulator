#pragma once
#include "Wire2.h"
#include "Structs.hpp"
#include "ParentTest.hpp"
#include <TimerOne.h>

/*
This is a simple test that just sets the value of the payload to a high tank level value and maintains that value
*/
class StableHigh : public ParentTest {
private:

void setCaliData() override; // sets some basic calibration data

// all these functions just set some basic values to the payload object
void setTempADC(uint16_t ADCVal);

void setTempOffset(uint8_t tempOffsetVal);

void setDielectric(uint16_t dielectricVal);

void setPulseCount(uint16_t pulseVal);


public:

StableHigh(); // constructor

void runTest() override; // starts running the test
};