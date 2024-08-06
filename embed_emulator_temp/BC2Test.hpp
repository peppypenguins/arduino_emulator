#pragma once
#include <TimerOne.h>
#include "Structs.hpp"
#include "ParentTest.hpp"



/*
This test is used to emulate the behaivors that the BC2 probe saw outside during a tank fill. The test is set to the exact same config data
and iterates over the exact same pulse count and raw count data that BC2 saw during a tank fill.
*/
class BC2 : public ParentTest{
private:
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function
static int interruptCounter; //used to see how many times the interrupt function has been called
static int values[20];
static int tempValues[20];
static int valuesItr;



void setCaliData() override; // sets some basic calibration data

static void countTimer();

static void timerInterrupt();

public:

BC2();

void runTest() override;


};
