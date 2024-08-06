#pragma once
#include <TimerOne.h>
#include "Structs.hpp"
#include "ParentTest.hpp"


/*
Counts increase by 50 every 20 seconds repeatedly. If the counts go above 1400 they revert back to 800.
*/
class Dt124Test : public ParentTest {

private:
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function
static int interruptCounter; //used to see how many times the interrupt function has been called

void setCaliData() override; // sets some basic calibration data

static void countTimer();

static void timerInterrupt();


public:

Dt124Test();

void runTest() override;

};