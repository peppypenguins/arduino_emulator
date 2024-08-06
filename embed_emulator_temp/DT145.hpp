#pragma once
#include <TimerOne.h>
#include "Structs.hpp"
#include "ParentTest.hpp"


/*
every 20 seconds the counts increase by 20. The counts will stop increasing once they are above 1400
*/
class Dt145Test : public ParentTest {

private:
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function
static int interruptCounter; //used to see how many times the interrupt function has been called

void setCaliData() override; // sets some basic calibration data

static void countTimer();

static void timerInterrupt();


public:

Dt145Test();

void runTest() override;

};