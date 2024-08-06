#pragma once
#include <TimerOne.h>
#include "Structs.hpp"
#include "ParentTest.hpp"

/*
This tests purpose is to check if an error correctly propagates if the returned crc is invalid and if the head will return
to a normal state once the crc reverts to its correct value. To accomplish this the test alternates every 60 seconds between
a valid crc and a crc of 0.

*/
class Dt122Test : public ParentTest{
private:
static int timerCounter; // used to see how many timers are triggered before calling the interrupt function
static int valuesItr;



void setCaliData() override; // sets some basic calibration data

static void countTimer();

static void timerInterrupt();

public:

Dt122Test();

void runTest() override;


};