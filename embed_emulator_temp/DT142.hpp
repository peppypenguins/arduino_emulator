#pragma once
#include <TimerOne.h>
#include "Wire2.h"
#include "Structs.hpp"
#include "ParentTest.hpp"


/*
This test goes over a range of invalid values. The valid values are between 770 and 1420. We should not see a 0 in the tank level if the BLE is working
correctly
*/

class Dt142Test : public ParentTest {

private:
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function
static int interruptCounter; //used to see how many times the interrupt function has been called
static int invalidValues[15];
static int invalidItr;

void setCaliData() override; // sets some basic calibration data

static void countTimer();

static void timerInterrupt();


public:

Dt142Test();

void runTest() override;

};