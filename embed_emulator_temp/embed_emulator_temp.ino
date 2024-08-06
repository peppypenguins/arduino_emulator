
#include "Structs.hpp"
#include "Slave.hpp"
#include "TestRoot.hpp"
#include "ParentTest.hpp"
#include "CoarseModeTest.hpp"
#include "IncrementTest.hpp"



/*
Apparently all arduino libraries must be used with static variables and functions, which must be initialized
outside of the class. Thus i am initializing them here. I believe it would be better to init them inside the 
header guards, but i cant get it to work so far. Will try to come back to this.

EDIT : Fixed, but will leave to help remind myself plus others if they have the same issue
*/

/*
Im using a single payload object across both the testing objects and the slave object so that everything is synchronized.
In setup i create a single payload pointer to pass to all of my other objects to use. I also create a slave embedded board with address
0x4 which the master head is set to communicate with. Finally i create a test object and set it to run whatever test i want. At the moment of writing this
it is set to COARSEMODETEST. All available test are located in the TEST enum in Structs.hpp, if adding a new test create a child class of the ParentTest
wrapper and inside of TestRoot add to the createTestObject your new test object corresponding to the name that you place into the TEST enum. Currently the 
test inside of the TEST enum are as follows, however not all of them are implemented yet.


enum TestEnum {
INCREMENTTEST,
COARSEMODETEST,
STABLETEST,
FILLTEST,
DT124,
DT130,
DT138,
DT142,
DT144,
DT145,
TESTENUMSIZE
};
*/





void setup() { // im just using setup like main
  Serial.begin(115200);
  Payload* testPayload = new Payload; // create the payload structure to be used
TestRoot testObject(testPayload);
int myTest = requestInput();
testObject.runTest(myTest);
Slave testSlave(0x4, testPayload);
while(true){

}
delete testPayload;
}

void loop() {
}
