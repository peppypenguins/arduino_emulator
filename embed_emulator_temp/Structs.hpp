#pragma once
#include "stdint.h"
#include <Arduino.h>

/*
This file i have designed to be shared by all other files so that any core structs/classes are declared in the 
same location.
*/

int selectTest(int input);
int requestInput();

/*
Basic Enum used across the project to determine what test you actually want to be running.
If i ever get around to it could maybe make a windows interface with this. Sounds like a lot of 
work tho
*/
enum TestEnum {
INCREMENTTEST,
COARSEMODETEST,
STABLETEST,
FILLTEST,
BC2TEST,
DT124,
DT130,
DT138,
DT142,
DT144,
DT145,
DT122,
STABLEHIGH,
STABLELOW,
FILLPRECISION,
TESTENUMSIZE
};


// basic pulse counts struct used for cali data
typedef struct {
uint16_t height;
uint16_t pcount;

}pcountPair;


/*
This is the Payload class that represents the current state of the emulated embedded board. I have included some methods
to make I2C easier by converting 16 bit numbers and arrays/structs into the byte format that they actually need to be in.
All of the members of this class (besides arrays) are initialized but i have been setting the values to what i actually want 
inside of my test objects for each test.
*/


 class Payload {
public:
uint16_t pcounts = 1000; // pulse counts
uint16_t NVMword[32]; // array of 32, 16 bit NVM words. never used so far but included anyways.
pcountPair caliData[10];// the calibration data held as 10 pcountPairs
uint8_t tankIndex = 0; // current selected tank type
uint8_t operatingMode = 0; // current operating mode
uint8_t hardwareVersion = 0; // current hardware version
uint8_t firmwareVersion = 0; // current firmware version
uint16_t probeLength = 4220; // current probe length
uint16_t dielectric = 2400; // current dielectric
uint8_t samplingMode = 2; // current sampling mode
uint16_t probeOffset = 260; // current probe offset
uint16_t tempADC = 820; // current temp ADC
int8_t tempOffset = 5; // current temp offset

uint8_t sleepMins = 0x5;
uint16_t sleepSec = 0x5000;
uint16_t timeMeasure = 0x1010;
uint16_t PWM = 0x0100;
uint16_t fillThresh = 0x0004;

bool newCRC = true;



/*
This function sets an array for what the calibration data should be then returns it. Typically to the
slave/master on I2C for transmit purposes. 
*/
void caliToBytes(byte* inputArray){

for (int i = 0; i < 10; ++i){
  byte currCount[2];
  byte currHeight[2];
 wordToBytes(caliData[i].pcount, currCount);
 wordToBytes(caliData[i].height, currHeight);
inputArray[(4*i) + 0] = currHeight[1];
inputArray[(4*i) + 1] = currHeight[0];
inputArray[(4*i) + 2] = currCount[1];
inputArray[(4*i) + 3] = currCount[0];
}
}



/*
This function converts the NVM array into 64 actual bytes of data to be sent over I2C. Never used so far but built anyway.

*/

void NVMToBytes(byte* inputArray){
for (int i = 0; i < 32; ++i){
byte NVMBytes[2];
wordToBytes(NVMword[i], NVMBytes);
inputArray[(i*2)] = NVMBytes[0];
inputArray[(i*2) + 1] = NVMBytes[1];
}
}


/*
This is the extended calibration data that seems to be sent to the master on startup. uses cali data plus
some other useful information and sends it to the sensor head. 
*/

void allCaliData(byte* inputArray){
for (int i = 0; i < 10; ++i){ // cali data
byte currCount[2];
 wordToBytes(caliData[i].pcount, currCount);
byte currHeight[2];
 wordToBytes(caliData[i].height, currHeight);
inputArray[(4*i) + 0] = currHeight[1];
inputArray[(4*i) + 1] = currHeight[0];
inputArray[(4*i) + 2] = currCount[1];
inputArray[(4*i) + 3] = currCount[0];
}

byte dielectricTemp[2];
 wordToBytes(dielectric, dielectricTemp);
byte probeLengthTemp[2];
 wordToBytes(probeLength, probeLengthTemp);
byte probeOffsetTemp[2];
 wordToBytes(probeOffset, probeOffsetTemp);



inputArray[40] = dielectricTemp[0];
inputArray[41] = dielectricTemp[1];
inputArray[42] = probeLengthTemp[0];
inputArray[43] = probeLengthTemp[1];
inputArray[44] = tankIndex;
inputArray[45] = hardwareVersion;
inputArray[46] = firmwareVersion;
inputArray[47] = probeOffsetTemp[0];
inputArray[48] = probeOffsetTemp[1];
inputArray[49] = tempOffset;
inputArray[50] = Fast_CRC_Cal8Bits(0,50,inputArray); // random value cause i dont know what crc is 

}


/*
This is the data cosntantly being sent to the head once I2C handshake has finished successfully. includes pulse counts
and temperature counts, plus CRC.
*/
void allCounts(byte* inputArray){
byte pCountsTemp[2];
uint16_t sendCounts = (samplingMode == 0) ? pcounts/5 : pcounts;
 wordToBytes(sendCounts, pCountsTemp);
byte tempADCTemp[2];
wordToBytes(tempADC, tempADCTemp);

inputArray[0] = pCountsTemp[0];
inputArray[1] = pCountsTemp[1];
inputArray[2] = tempADCTemp[0];
inputArray[3] = tempADCTemp[1];
if (newCRC){
inputArray[4] = newCRCFunc(pCountsTemp[0], pCountsTemp[1], tempADCTemp[0], tempADCTemp[1]);
}
else{
inputArray[4] = 0;
}
}

void currConfig(byte* inputArray){
inputArray[0] = (sleepMins & 0xF0) | (uint8_t)((sleepSec >> 12)& 0x0F);
inputArray[1] = (uint8_t)(sleepSec & 0x00FF);
inputArray[2] = (uint8_t)((timeMeasure >> 8) & 0x00FF);
inputArray[3] = (uint8_t)((timeMeasure& 0x00FF));
inputArray[4] = (uint8_t)((PWM >> 8) & 0x00FF);
inputArray[5] = (uint8_t)(PWM&0x00FF);
inputArray[6] = samplingMode;
inputArray[7] = (uint8_t)((fillThresh >> 8) & 0x00FF);
inputArray[8] = (uint8_t)(fillThresh & 0x00FF);
}


/*
This function converts a 16 bit unsigned int into an array of 2 bytes. Used 
with other functions to return data to master/slave. for instance to convert the pulse counts 
into two bytes to be used in the allCounts() function. The slave can also call this function 
if it wants to send say, the temperature ADC. 
*/
void wordToBytes(uint16_t inputWord, uint8_t* inputArray){
byte MSB = (byte)(inputWord >> 8);
byte LSB = (byte)(inputWord&0xFF);
inputArray[0] = MSB;
inputArray[1] = LSB;
}


/*
This sets the calibration data of the payload based off the 10 pcount pairs it is given.
Typically used in test objects to set the calibration data to what they want for the test.
*/
void setCaliData(pcountPair pairs[10]){
  for (int i = 0; i < 10;++i){
caliData[i] = pairs[i];
  }
}

/*
This is a function i took from the source code for the embedded PIC code. I do not know if this is actually
functioning properly since i don't know what the CRC should be in reality. However i am using it to calc my
CRC
*/
uint8_t Fast_CRC_Cal8Bits(uint8_t crc, int Size, uint8_t *Buffer) {
    static const uint8_t CrcTable[] = {// 0x97 Polynomial Table, 8-bit
        0x00, 0x97, 0xB9, 0x2E, 0xE5, 0x72, 0x5C, 0xCB,
        0x5D, 0xCA, 0xE4, 0x73, 0xB8, 0x2F, 0x01, 0x96,
        0xBA, 0x2D, 0x03, 0x94, 0x5F, 0xC8, 0xE6, 0x71,
        0xE7, 0x70, 0x5E, 0xC9, 0x02, 0x95, 0xBB, 0x2C,
        0xE3, 0x74, 0x5A, 0xCD, 0x06, 0x91, 0xBF, 0x28,
        0xBE, 0x29, 0x07, 0x90, 0x5B, 0xCC, 0xE2, 0x75,
        0x59, 0xCE, 0xE0, 0x77, 0xBC, 0x2B, 0x05, 0x92,
        0x04, 0x93, 0xBD, 0x2A, 0xE1, 0x76, 0x58, 0xCF,
        0x51, 0xC6, 0xE8, 0x7F, 0xB4, 0x23, 0x0D, 0x9A,
        0x0C, 0x9B, 0xB5, 0x22, 0xE9, 0x7E, 0x50, 0xC7,
        0xEB, 0x7C, 0x52, 0xC5, 0x0E, 0x99, 0xB7, 0x20,
        0xB6, 0x21, 0x0F, 0x98, 0x53, 0xC4, 0xEA, 0x7D,
        0xB2, 0x25, 0x0B, 0x9C, 0x57, 0xC0, 0xEE, 0x79,
        0xEF, 0x78, 0x56, 0xC1, 0x0A, 0x9D, 0xB3, 0x24,
        0x08, 0x9F, 0xB1, 0x26, 0xED, 0x7A, 0x54, 0xC3,
        0x55, 0xC2, 0xEC, 0x7B, 0xB0, 0x27, 0x09, 0x9E,
        0xA2, 0x35, 0x1B, 0x8C, 0x47, 0xD0, 0xFE, 0x69,
        0xFF, 0x68, 0x46, 0xD1, 0x1A, 0x8D, 0xA3, 0x34,
        0x18, 0x8F, 0xA1, 0x36, 0xFD, 0x6A, 0x44, 0xD3,
        0x45, 0xD2, 0xFC, 0x6B, 0xA0, 0x37, 0x19, 0x8E,
        0x41, 0xD6, 0xF8, 0x6F, 0xA4, 0x33, 0x1D, 0x8A,
        0x1C, 0x8B, 0xA5, 0x32, 0xF9, 0x6E, 0x40, 0xD7,
        0xFB, 0x6C, 0x42, 0xD5, 0x1E, 0x89, 0xA7, 0x30,
        0xA6, 0x31, 0x1F, 0x88, 0x43, 0xD4, 0xFA, 0x6D,
        0xF3, 0x64, 0x4A, 0xDD, 0x16, 0x81, 0xAF, 0x38,
        0xAE, 0x39, 0x17, 0x80, 0x4B, 0xDC, 0xF2, 0x65,
        0x49, 0xDE, 0xF0, 0x67, 0xAC, 0x3B, 0x15, 0x82,
        0x14, 0x83, 0xAD, 0x3A, 0xF1, 0x66, 0x48, 0xDF,
        0x10, 0x87, 0xA9, 0x3E, 0xF5, 0x62, 0x4C, 0xDB,
        0x4D, 0xDA, 0xF4, 0x63, 0xA8, 0x3F, 0x11, 0x86,
        0xAA, 0x3D, 0x13, 0x84, 0x4F, 0xD8, 0xF6, 0x61,
        0xF7, 0x60, 0x4E, 0xD9, 0x12, 0x85, 0xAB, 0x3C
    };

    while (Size--) {
        crc = crc ^ *Buffer++; // Apply Byte
        crc = CrcTable[crc & 0xFF]; // One round of 8-bits
    }
    return (crc);
}
uint8_t newCRCFunc(uint8_t buff0, uint8_t buff1, uint8_t buff2, uint8_t buff3){
  uint8_t initXOR = 0xAA;
  if (samplingMode == 1){
    initXOR = 0xAB;
  } else if (samplingMode == 2){
    initXOR = 0xA9;
  }

uint8_t crc = initXOR ^ buff0;
crc ^= buff1;
crc ^= buff2;
crc ^= buff3;
return crc;
}

};