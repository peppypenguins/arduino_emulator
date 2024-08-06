
#include "Slave.hpp"

byte Slave::RxBytes[51] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0};
byte* Slave::TxBytes = new byte[64]; /* i am currently statically allocating this memory since we will be needing it throughout the whole program
you can probably allocate it as needed in the Slave class but it could get dangerous
*/
int Slave::numBytes = 0;
int Slave::numReceive = 0;
int Slave::TxCounter = 2;
bool Slave::readBFWrite = true;
bool Slave::justWrote = true;
Payload* Slave::currPayload = nullptr;

    void Slave::I2C_RxHandler(int numBytes) {
            numReceive = 0;
      while (Wire.available()){
            RxBytes[numReceive] = Wire.read();
            numReceive++;
            }      // read the singular byte that the master should send
            Serial.print("receieved request: 0x");
Serial.println(RxBytes[0],HEX);
        updateTx(RxBytes[0]);  // calls the function that updates the Transmit bytes
        readBFWrite = true;

    }




    void Slave::I2C_TxHandler() {   
      if (!justWrote){ // only transmit if there was not a write during the last sent cmd
             if (!readBFWrite){ // if there was not a read before this write update the bytes to be send to be the null cmd
        updateTx(0);
      }
            messageFunc(); // sends a message to the serial port of what is actually being transmitted. helpful for debugging
        Wire.write(TxBytes, numBytes);
        readBFWrite = false;
    } else {
      updateTx(0);
    }
    justWrote = false;
    }



 /*
This function updates the bytes that will be transmit when the master requests data. it does this by receiving a pointer to an 
array that has been allocated by the payload class. Since as of right now the payload class will not send data greater than 64 bytes 
TxBytes is allocated at the beginning of the program to 64 bytes. TxBytes is updated by memcpy from the received data and then we delete
the unneeded allocated array. We must set the numBytes currently since this is what is used in the TxHandler to know how many bytes to send.
*/
    void Slave::updateTx(byte cmd) {
justWrote = false;
      Serial.print("Update Tx, cmd:0x");
      Serial.println(cmd,HEX);

        RxBytes[0] = cmd;
        switch (cmd) {
          case 0x00:currPayload->allCounts(TxBytes);
          numBytes = 5;
          break;
            case 0x01:if (numReceive < 2){
                 currPayload->wordToBytes(currPayload->pcounts, TxBytes);
                numBytes = 2;
            } else {
              currPayload->pcounts = (((uint16_t)RxBytes[1]) << 8) | (uint16_t)(RxBytes[2]);
            }
                break;
            case 0x04:if (numReceive < 2){
                currPayload->caliToBytes(TxBytes);
                numBytes = 40;
            } else {
              for(int i = 0; i < 10; ++i){
                currPayload->caliData[i].pcount = (uint16_t)(RxBytes[1 + (i*4) ]) | (((uint16_t)(RxBytes[2 + (i*4)])) << 8);
                currPayload->caliData[i].height = (uint16_t)(RxBytes[3 + (i*4) ]) | (((uint16_t)(RxBytes[4 + (i*4)])) << 8);
              }
            }
                break;
            case 0x05: if (numReceive < 2) {
            TxBytes[0] = currPayload->tankIndex;
                numBytes = 1;
            } else {
              currPayload->tankIndex = RxBytes[1];
            }
                break;
            case 0x06: if (numReceive < 2){
            TxBytes[0] = currPayload->operatingMode;
                numBytes = 1;
            } else {
              currPayload->operatingMode = RxBytes[1];
            }
                break;
            case 0x08: if (numReceive < 2){
            TxBytes[0] = currPayload->hardwareVersion;
                numBytes = 1;
            } else {
              currPayload->hardwareVersion = RxBytes[1];
            }
                break;
            case 0x09: if (numReceive < 2){
            TxBytes[0] = currPayload->firmwareVersion;
                numBytes = 1;
            } else {
              currPayload->firmwareVersion = RxBytes[1];
            }
                break;
            case 0x10: if (numReceive < 2){
                currPayload->wordToBytes(currPayload->probeLength, TxBytes);
                numBytes = 2;
            } else {
              currPayload->probeLength = (((uint16_t)RxBytes[1]) << 8) | (uint16_t)(RxBytes[2]);
            }
                break;
            case 0x11: if (numReceive < 2){
                currPayload->wordToBytes(currPayload->dielectric, TxBytes);
                numBytes = 2;
            } else {
              currPayload->dielectric = (((uint16_t)RxBytes[1]) << 8) | (uint16_t)(RxBytes[2]);
            }
                break;
            case 0x12:
            if (numReceive > 1){
              justWrote = true;
                currPayload->samplingMode = RxBytes[1];
            } else {
                TxBytes[0] = currPayload->samplingMode;
                numBytes = 1;
            }
                break;
            case 0x13: if (numReceive  < 2) {
                 currPayload->wordToBytes(currPayload->probeOffset, TxBytes);
                numBytes = 2;
            } else {
              currPayload->probeOffset = (((uint16_t)RxBytes[1]) << 8) | (uint16_t)(RxBytes[2]);
            }
                break;
            case 0x14: if (numReceive < 2) {
                currPayload->wordToBytes(currPayload->tempADC, TxBytes);
                numBytes = 2;
            } else {
              currPayload->tempADC = (((uint16_t)RxBytes[1]) << 8) | (uint16_t)(RxBytes[2]);
            }
                break;
            case 0x15: if (numReceive < 2) {
                TxBytes[0] = currPayload->tempOffset;
                numBytes = 1;
            } else {
              currPayload->tempOffset = (((uint16_t)RxBytes[1]) << 8) | (uint16_t)(RxBytes[2]);
            }
                break;
            case 0x0E:
if (numReceive > 1) {
currPayload->sleepMins = RxBytes[1] >> 4;
currPayload->sleepSec = (((uint16_t)RxBytes[1] << 12 ) & 0xFF00) | (RxBytes[2]);
currPayload->timeMeasure = ((uint16_t)RxBytes[3] << 8) | (RxBytes[4]);
currPayload->PWM = ((uint16_t)RxBytes[5] << 8) | (RxBytes[6]);
currPayload->samplingMode = RxBytes[7];
currPayload->fillThresh = ((uint16_t)RxBytes[8] << 8) | (RxBytes[9]);
numReceive = 0;
justWrote = true;
} else {
currPayload->currConfig(TxBytes);
                numBytes = 9;
}
                break;
            case 0x0F:
            if (numReceive < 2){
            currPayload->allCaliData(TxBytes);
                numBytes = 51;
        } else {
           justWrote = true;
        }
                break;
            case 0x0D:currPayload->NVMToBytes(TxBytes);
            numBytes = 64;
                break;
        }
        numReceive = 0;
    }




 void Slave::messageFunc(){ // just a function to send a message to serial line
 
        Serial.print("Current PCounts:0x");
        Serial.println(currPayload->pcounts,HEX);
        Serial.print("sent transmit cmd:0x");
        Serial.println(RxBytes[0],HEX);
        int tempNum = 0;
        while(tempNum < numBytes){
Serial.print("Byte #");
Serial.print(tempNum);
Serial.print(": 0x");
Serial.println(TxBytes[tempNum],HEX);
          tempNum++;
        }


}




    /* Constructor that initializes the I2C bus. TxBytes is set to cmd 0 since it is
    the most informative to myself for debugging. Then we set the wireclock so that 
    the I2C is communicating at the correct speed. Then set the functions to be called when a message is received
    from the master to be RxHandler and when the master requests a transmit to TxHandler
    */
    Slave::Slave(int address, Payload* inputPayload) {
      currPayload = inputPayload;
      Serial.println("init I2C");
      updateTx(0x00);
            Wire.setClock( 100000UL);
        Wire.begin(address);
        Wire.onReceive(I2C_RxHandler);
        Wire.onRequest(I2C_TxHandler);
    }

    Slave::~Slave(){ // if for whatever reason this object is deleted correspondingly delete TxBytes to prevent dangling ptr
      delete[] TxBytes;
    }

