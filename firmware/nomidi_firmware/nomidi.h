/*
  This file is part of
  NOMIDI - A OSC based performance controller

  Copyright (c) 2021 by Ralf Baecker <rlfbckr ~AT~ gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>
#include <OSCBundle.h>
#include <Chrono.h>
#include "SevSeg.h"
#include "MUX74HC4067.h"
#include "config.h"
#include "animation.h"

#define _VERSION_ 0.06

boolean _SETUPMODE_ = false;

int setup_pos = 0;
int setup_pos_max = 2;
int setup_brighness = 60;

boolean BUTTON_SWI = false;
boolean BUTTON_PRE = false;
boolean BUTTON_NXT  = false;
boolean BUTTON_SEL = false;


volatile char segmentData[] = "----------";
const byte segCathodePins[] = {19, 20, 21, 22, 23, 24, 25, 26, 27, 38};
const byte segAnodePins[] = {39, 40, 41, 30, 31, 28, 29, 34};


const int ledPins[] = {0, 1, 35, 11, 12, 13, 32, 33, 36, 37};
volatile int ledIntesity[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile int softPWMtic = 0;
volatile int softPWMres = 100;

const float inputValueSmoothing = 0.2; // the smaller the smoother
const float inputValueGain = 1.003;
const int inputValueLowCut = 5;
const int inputValueHighCut = 4090;
const int inputHysteresisMax = 15;
const int inputHysteresisMin = 1;

const int ADDR_A = 2;
const int ADDR_B = 3;
const int ADDR_C = 4;
const int ADDR_D = 5;

const int POT1_X = A3;
const int POT1_INH = 9;
volatile int POT1_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};
volatile int POT1_VALUES_LAST[] = { -111 , -111, -111, -111, -111, -111, -111, -111, -111, -111};
volatile int POT1_HYS[] = { inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax };
volatile long POT1_HYS_LAST_CHANGE[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const int POT0_X = A2;
const int POT0_INH = 8;
volatile int POT0_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};
volatile int POT0_VALUES_LAST[] = { -111 , -111, -111, -111, 111, 111 , -111, -111, -111, -111};
volatile int POT0_HYS[] = { inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax };
volatile long POT0_HYS_LAST_CHANGE[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const int FADER_X = A0;
const int FADER_INH = 6;
volatile int FADER_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};
volatile int FADER_VALUES_LAST[] = { -111 , -111, -111, -111, -111, -111 , -111, -111, -111, -111};
volatile int FADER_HYS[] = { inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax, inputHysteresisMax };
volatile long FADER_HYS_LAST_CHANGE[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const int BUTTON0_X = 15;
const int BUTTON0_INH = 7;
volatile int BUTTON0_VALUES_LAST[] = { -1 , -1, -1, -1, -1, -1 , -1, -1, -1, -1};
volatile int BUTTON0_VALUES_LAST_SEND[] = { -1 , -1, -1, -1, -1, -1 , -1, -1, -1, -1};
volatile int BUTTON0_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};
volatile long BUTTON0_PUSHTIME_START[] = { -1 , -1, -1, -1, -1, -1 , -1, -1, -1, -1};
volatile long BUTTON0_PUSHTIME[] = { -1 , -1, -1, -1, -1, -1 , -1, -1, -1, -1};

const int BUTTON1_X = A4;
const int BUTTON1_INH = 10;
volatile int BUTTON1_VALUES_LAST[] = { -1 , -1, -1, -1, -1, -1 , -1, -1, -1, -1};
volatile int BUTTON1_VALUES_LAST_SEND[] = { -1 , -1, -1, -1, -1, -1 , -1, -1, -1, -1};
volatile int BUTTON1_VALUES[] = { 0 , 0, 0, 0, 0, 0 , 0, 0, 0, 0};
volatile long BUTTON1_PUSHTIME_START[] = { -1 , -1, -1, -1, -1, -1 , -1, -1, -1, -1};
volatile long BUTTON1_PUSHTIME[] = { -1 , -1, -1, -1, -1, -1 , -1, -1, -1, -1};


#ifdef USE_SLIP_SERIAL
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial( SerialUSB );
#endif



IntervalTimer updateDisplayTimer;
IntervalTimer softPWMTimer;
Chrono sendOSC;
Chrono readInputsChrono;

MUX74HC4067 mux_pot1(POT1_INH, ADDR_A, ADDR_B, ADDR_C, ADDR_D);
MUX74HC4067 mux_pot0(POT0_INH, ADDR_A, ADDR_B, ADDR_C, ADDR_D);
MUX74HC4067 mux_fader(FADER_INH, ADDR_A, ADDR_B, ADDR_C, ADDR_D);
MUX74HC4067 mux_button0(BUTTON0_INH, ADDR_A, ADDR_B, ADDR_C, ADDR_D);
MUX74HC4067 mux_button1(BUTTON1_INH, ADDR_A, ADDR_B, ADDR_C, ADDR_D);


#ifdef USE_ETHERNET
EthernetUDP Udp;
#endif

SevSeg sevseg;
