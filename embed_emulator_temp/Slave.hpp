#pragma once
#include "Wire2.h"
#include "Structs.hpp"



/* This is the class used to create and handle an I2C slave, specifically one to emulate the embedded board.
If you want a similar I2C slave you can simply alter the Rx handler to update the TxBytes differently.


Currently the slave updates the bytes that it plans to send based off of the messages it receives from the master.
If it receives a valid cmd from the master it will change its data to send to the corresponding data. If the slave receives two or more transmit requests 
in a row without being sent a cmd it defaults to sending the bytes for cmd 0.
*/


class Slave {
private:
    static byte RxBytes[51]; // i believe is unnecessary to be a class member but will remain for the moment
    static byte* TxBytes;
    static int numBytes;
    static int numReceive;
    static Payload* currPayload;
    static bool readBFWrite;
  static int TxCounter;
static bool justWrote;

    static void I2C_RxHandler(int numBytes); // handles bytes received

    static void I2C_TxHandler(); // handles transmit requests

    static void updateTx(byte cmd);

    static void messageFunc();// just a function to send a message to serial line

public:

    Slave(int address,Payload* inputPayload); // constructor

    ~Slave(); // destructor

        void Slave::setCurrPayload(Payload* payload) { // this function lets you set the payload to whatever payload you want. Should probably be moved to constructor but ran into problems.
    currPayload = payload;
    }

};

