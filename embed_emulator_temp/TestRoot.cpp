
#include "TestRoot.hpp"

Payload* TestRoot::testPayload = nullptr;

/*
This function allocates memory for the requested test and returns its pointer to be used to run whatever 
requested test. Should be deleted inside the destructor if the testRoot is ever deleted
*/
ParentTest* TestRoot::createTestObject(int testNum){ 
    switch(testNum){
      case INCREMENTTEST: return new IncrementTest;
      break;
      case COARSEMODETEST: return new CoarseModeTest;
      break;
      case STABLETEST: return new StableTest;
      break;
      case FILLTEST: return new FillTest;
      break;
      case BC2TEST: return new BC2;
      break;
      case DT130: return new DT130TEST;
      break;
      case DT124: return new Dt124Test;
      break;
      case DT138: return new Dt138Test;
      break;
      case DT142: return new Dt142Test;
      break;
      case DT144: return new Dt144Test;
      break;
      case DT145: return new Dt145Test;
      break;
      case DT122: return new Dt122Test;
      break;
      case STABLEHIGH: return new StableHigh;
      break;
      case STABLELOW: return new StableLow;
      break;
      case FILLPRECISION: return new FillPrecision;
      break;
      default : return nullptr;
      break;
    }
}



TestRoot::TestRoot(Payload* inputPayload){ // constructor that inits the payload to whatever pointer is given to the object
  testPayload = inputPayload;
}

TestRoot::~TestRoot(){
  Serial.println("delete test");
  for (int i = 0; i < TESTENUMSIZE;++i){
    if (testArray[i] != nullptr){
delete testArray[i];
    }
  }
}


void TestRoot::runTest(int testNumber){ // this starts whatever test is requested 
testArray[testNumber] = createTestObject(testNumber); // creates desired test object
testArray[testNumber]->setPayload(testPayload);
testArray[testNumber]->setCaliData();
testArray[testNumber]->caliInit();
  testArray[testNumber]->runTest(); // starts running the test
}



