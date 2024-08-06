#pragma once
#include "Wire2.h"
#include "Structs.hpp"
#include "ParentTest.hpp"
#include <TimerOne.h>



/*
This was an old test for an older style of the emulator. This test has been repurposed to trigger a single a fill mode
and then maintain the counts and allow the mode to revert back to coarse mode.
*/


class CoarseModeTest : public ParentTest {
private:
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function
static int interruptCounter; //used to see how many times the interrupt function has been called


static void countTimer();

static void timerInterrupt(); // timer interrupt to simulate coarse mode

void setCaliData() override; // sets some basic calibration data

protected:

public:

CourseModeTest(); // constructor

void runTest() override; // starts running the test


};
