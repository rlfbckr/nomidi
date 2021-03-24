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

#include "nomidi.h"


#ifdef USE_SLIP_SERIAL
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#endif

/*
   Teensy 4.1
   Settings
   CPU Speed: 600 Mhz
   USB-Type:  Serial

*/


volatile int readinputtick = 0;
IntervalTimer readInputsTimer;
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

void setup() {
#ifdef USE_SLIP_SERIAL
  SLIPSerial.begin(115200);
#else
  Serial.begin(115200);
  Serial.print("NOMIDI v");
  Serial.println(  _VERSION_);
#endif

  analogReadResolution(12);
  mux_pot1.signalPin(POT1_X, INPUT, ANALOG);
  mux_pot0.signalPin(POT0_X, INPUT, ANALOG);
  mux_fader.signalPin(FADER_X, INPUT, ANALOG);
  mux_button0.signalPin(BUTTON0_X, INPUT, ANALOG);
  mux_button1.signalPin(BUTTON1_X, INPUT, ANALOG);

  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = N_TRANSISTORS  ; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, 10, segCathodePins, segAnodePins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(setup_brighness);
  analogReadAveraging(100);
#ifdef USE_ETHERNET
  initEthernet();
#endif
  updateDisplayTimer.begin(updateSevenSegment, 250);
  softPWMTimer.begin(updateSoftPWM, 100);
}

void loop() {
  if (_SETUPMODE_) {
    setupMode();
  }
  if (readInputsChrono.hasPassed(10) ) {
    readInputsChrono.restart();
    readInputs();
  }
  if (sendOSC.hasPassed(30) ) {
    sendOSC.restart();
    sendInputsOSC();
  }

  drawAnimation();
  
#ifdef USE_ETHERNET
  OSCMessage msgIn;
  int msg_size;
  if ((msg_size = Udp.parsePacket()) > 0) {
    while (msg_size--)
      msgIn.fill(Udp.read());
    if (!msgIn.hasError()) {
      msgIn.route("/nm/set7seg", OSCset7Seg);
      msgIn.route("/nm/set7segall", OSCset7SegAll);
      msgIn.route("/nm/setled", OSCsetLED);
      msgIn.route("/nm/sendall", OSCsendAll);
    }
  }
#endif
}

void updateSevenSegment() {
  sevseg.setChars(segmentData);
  sevseg.refreshDisplay();
}
