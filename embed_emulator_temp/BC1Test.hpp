#pragma once
#include <TimerOne.h>
#include "Structs.hpp"
#include "ParentTest.hpp"

class BC1 : public ParentTest{
private:
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function
static int interruptCounter; //used to see how many times the interrupt function has been called
static int values[10];
static int valuesItr;



void setCaliData() override; // sets some basic calibration data

static void countTimer();

static void timerInterrupt();

public:

BC1();

void runTest() override;


};
