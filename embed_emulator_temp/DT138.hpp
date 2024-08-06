#pragma once
#include <TimerOne.h>
#include "Wire2.h"
#include "Structs.hpp"
#include "ParentTest.hpp"


/*
This test has the counts start at 1400 then decrease consistently every 28 seconds by 45. This should allow for averaging to occur once a precision measurement
is read. Then once the counts go below 1100 it restarts at 1400 triggering a fill mode.
*/

class Dt138Test : public ParentTest {

private:
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function
static int interruptCounter; //used to see how many times the interrupt function has been called

void setCaliData() override; // sets some basic calibration data

static void countTimer();

static void timerInterrupt();


public:

Dt138Test();

void runTest() override;

};