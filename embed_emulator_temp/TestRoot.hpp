#pragma once
#include "Structs.hpp"
#include "ParentTest.hpp"
#include "IncrementTest.hpp"
#include "CoarseModeTest.hpp"
#include "StableTest.hpp"
#include "DT130.hpp"
#include "FillTest.hpp"
#include "DT144.hpp"
#include "DT138.hpp"
#include "DT142.hpp"
#include "DT145.hpp"
#include "DT124.hpp"
#include "BC2Test.hpp"
#include "DT122.hpp"
#include "StableLow.hpp"
#include "StableHigh.hpp"
#include "FillPrecision.hpp"


/*
This is the root of the Testing. You should only create one of these objects and when you tell this object to run a test it will
create the desired test object and start running the test requested.
*/


class TestRoot {
private:

static Payload* testPayload; // pointer to the global payload used across the slave and the tests
ParentTest* testArray[TESTENUMSIZE]; // this is an array of all the various test, starts as all null pointers

ParentTest* createTestObject(int testNum);// creates test object, currently using a switch case but will try to implement a factory function later

public:
TestRoot(Payload* inputPayload); // constructor

~TestRoot(); // destructor

void runTest(int testNumber); // starts running the desired test

};