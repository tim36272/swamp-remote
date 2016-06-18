/*
 * IRremote: IRsendRawDemo - demonstrates sending IR codes with sendRaw
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 *
 * IRsendRawDemo - added by AnalysIR (via www.AnalysIR.com), 24 August 2015
 *
 * This example shows how to send a RAW signal using the IRremote library.
 * The example signal is actually a 32 bit NEC signal.
 * Remote Control button: LGTV Power On/Off. 
 * Hex Value: 0x20DF10EF, 32 bits
 * 
 * It is more efficient to use the sendNEC function to send NEC signals. 
 * Use of sendRaw here, serves only as an example of using the function.
 * 
 */
//#define DEBUG_MODE

#include <IRremote.h>
#include <Manchester.h>
#include <SwampController.h>

IRsend irsend;

#define RX_PIN 0
#define IR_FREQ 38 // IR Frequency in kilohertz


unsigned int btnPump[] = {
1335,  348, 1332,  350,  495, 1190,
1339,  344, 1336,  347,  499, 1185,
 496, 1190,  497, 1184, 1352,  333,
 497, 1186,  494, 1187,  501, 7918,
1344,  343, 1341,  342,  499, 1185,
1366,  317, 1364,  320,  498, 1190,
 494, 1185,  498, 1187, 1339,  344,
 520, 1167,  492, 1193,  519};

 unsigned int btnPower[] = {
 1363 ,    319,    1365 ,    317,     528,    1157,
 1369 ,    317,    1366 ,    318,     523,    1158,
 526  ,  1159 ,   1369  ,   319 ,    557 ,   1127,
 523  ,  1159 ,    522  ,  1161 ,    527 ,   7891,
 1372 ,    317,    1366 ,    317,     524,    1158,
 1368 ,    316,    1377 ,    311,     523,    1159,
 550  ,  1134 ,   1369  ,   314 ,    528 ,   1152,
 557  ,  1134 ,    521  ,  1163 ,    522};

 unsigned int btnFan[] = {
1330,     349,    1336,     347,     492,    1191,
1337,     346,    1342,     342,     512,    1173,
498 ,   1182 ,    501 ,   1184 ,    499 ,   1185,
1341,     343,     498,    1186,     509,    7907,
1340,     346,    1377,     307,     498,    1186,
1366,     317,    1341,     343,     496,    1188,
524 ,   1159 ,    499 ,   1189 ,    520 ,   1163,
1337,     344,     522,    1164,     499};


uint8_t data;
uint8_t id;

void setup()
{  
  //#ifndef DEBUG_MODE
  man.setupReceive(RX_PIN, MAN_1200);
  man.beginReceive();
  //#endif
  Serial.begin(9600);
}

void loop() {
  if (man.receiveComplete()) { //received something
    uint16_t m = man.getMessage();
    if (man.decodeMessage(m, id, data)) { //extract id and data from message, check if checksum is correct
      if (id == DEVICE_ID) {
        switch(data) {
          case SWAMP_PUMP:
            irsend.sendRaw(btnPump, sizeof(btnPump) / sizeof(btnPump[0]), IR_FREQ); //Note the approach used to automatically calculate the size of the array.
            acknowledge(6000);
          break;
          case SWAMP_FAN:
            irsend.sendRaw(btnFan, sizeof(btnFan) / sizeof(btnFan[0]), IR_FREQ); //Note the approach used to automatically calculate the size of the array.
            acknowledge(6000);
          break;
          case SWAMP_POWER:
            irsend.sendRaw(btnPower, sizeof(btnPower) / sizeof(btnPower[0]), IR_FREQ); //Note the approach used to automatically calculate the size of the array.
            acknowledge(6000);
          break;
        }
      }
    }
    man.beginReceive(); //start listening for next message right after you retrieve the message
  }
}
