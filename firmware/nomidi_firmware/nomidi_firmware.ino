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
/*
  Borad:      Teensy 4.1
  USB Type:   USB Serial
  CPU Speed:  600 Mhz
*/


void setup() {
#ifdef USE_SLIP_SERIAL
  SLIPSerial.begin(1000000);
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
  initLED();
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
  readUdpOsc();
#endif

#ifdef USE_SLIP_SERIAL
  readSerialOSC();
#endif

}

#ifdef USE_ETHERNET
void readUdpOsc() {
  OSCMessage msgIn;
  int msg_size;
  if ((msg_size = Udp.parsePacket()) > 0) {
    while (msg_size--)
      msgIn.fill(Udp.read());
    if (!msgIn.hasError()) {
      msgIn.route("/nm/set7seg", OSCset7Seg);
      msgIn.route("/nm/set7segall", OSCset7SegAll);
      msgIn.route("/nm/setled", OSCsetLED);
    }
  }
}
#endif

#ifdef USE_SLIP_SERIAL
void readSerialOSC() {
  if (SLIPSerial.available()) {
    OSCBundle msgIn;

    int size;
    while (!SLIPSerial.endofPacket())
      if ((size = SLIPSerial.available()) > 0) {
        while (size--) msgIn.fill(SLIPSerial.read());
      }
    if (!msgIn.hasError()) {
      msgIn.route("/nm/set7seg", OSCset7Seg);
      msgIn.route("/nm/set7segall", OSCset7SegAll);
      msgIn.route("/nm/setled", OSCsetLED);
     // msgIn.route("/nm/sendall", OSCsendAll);

    }
  }
}
#endif

void action(OSCMessage &msg, int addrOffset) {
  //digitalWrite(ledPins[msg.getInt(0)], HIGH);
  ledIntesity[msg.getInt(0)] = 100;
  delay(100);
  ledIntesity[msg.getInt(0)] = 0;
}

void updateSevenSegment() {
  sevseg.setChars(segmentData);
  sevseg.refreshDisplay();
}
