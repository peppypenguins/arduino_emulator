#pragma once
#include <TimerOne.h>
#include "Wire2.h"
#include "Structs.hpp"
#include "ParentTest.hpp"

/*
This test increases the counts by 25 equating to about ~3% every 2 minutes. Once the counts reach 1400 they stay constant.
*/

class Dt144Test : public ParentTest {
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function
static int interruptCounter; //used to see how many times the interrupt function has been called

void setCaliData() override; // sets some basic calibration data

static void countTimer();

static void timerInterrupt();

public:

Dt144Test(); // constructor

void runTest() override; // starts running the test


};
