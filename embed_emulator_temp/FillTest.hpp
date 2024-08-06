#pragma once
#include <TimerOne.h>
#include "Wire2.h"
#include "Structs.hpp"
#include "ParentTest.hpp"


/*
Test that emulates a tank fill. The counts originally stay low for 1 minute before a fill begins. For the next minute the counts increase by about 15%
every 10 seconds. Then for the next 8 minutes the counts stay at around 75% full. then the test repeats.
*/
class FillTest : public ParentTest {
  private:
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function
static int interruptCounter; //used to see how many times the interrupt function has been called

void setCaliData() override; // sets some basic calibration data

static void countTimer();

static void timerInterrupt();

public:

FillTest(); // constructor

void runTest() override; // starts running the test

};