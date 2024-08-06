#pragma once
#include "Structs.hpp"



/* this class is used to create child classes of the actual tests under so that they can
be interchanged in data structures. Basically a wrapper class. For example to use them in an array together
*/



class ParentTest {
protected:
pcountPair baseCaliData[10]; // the calibration data that the child test wants to run under
static Payload* parentPayload; // the payload that the test will be using/modifying




public:

void setPayload(Payload* payloadSetup); // sets the payload to whatever the given pointer is

void caliInit();// initalizes the calibration data in the payload to whatever the test has its cali data as

virtual void runTest();// should never be run really. virtual function that child classes should implement

virtual void setCaliData();// base function to set calibration data but should be implemented in child class


};