#pragma once
#include <TimerOne.h>
#include "Structs.hpp"
#include "ParentTest.hpp"

/*
This tests purpose is to trigger a fill mode on a precision read. To accomplish this the counts will be set to 1000 when the sampling mode is either a 1 or 2.
And the counts will be set to 900 when the sampling mode is 1. The timer interrupt will trigger every o.5 seconds to detect what mode the payload is currently in.
*/
class FillPrecision : public ParentTest{
private:
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function
static int valuesItr;



void setCaliData() override; // sets some basic calibration data

static void countTimer();

static void timerInterrupt();

public:

FillPrecision();

void runTest() override;


};