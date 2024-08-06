#pragma once
#include "Wire2.h"
#include "Structs.hpp"
#include <TimerOne.h>
#include "ParentTest.hpp"



/*
This is a simple test that increases the pulse counts in a loop before restarting at 800

*/

class IncrementTest : public ParentTest {
private:
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function

static void countTimer();

void setCaliData() override;// sets some typical calibration data

static void timerInterrupt();// has pulse counts loop from 800-1500


public:

IncrementTest(); // constructor 

void runTest() override; // actually starts running the test

};