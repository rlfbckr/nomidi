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

void OSCsendAll(OSCMessage &msg, int addrOffset) {
  if (DEBUG_OSC_MSG) Serial.print("> /nm/sendAll ");
  //noInterrupts();
  for (int i = 0; i < 10; i++) {
    FADER_VALUES_LAST[i] = -111;
    POT0_VALUES_LAST[i] = -111;
    POT1_VALUES_LAST[i] = -111;
  }
  sendInputsOSC();
  //interrupts();
}



void OSCsetLED(OSCMessage &msg, int addrOffset) {
  if (DEBUG_OSC_MSG) Serial.print("> /nm/setLED ");
  int pos = msg.getInt(0);
  int intensity = msg.getInt(1);
  if (pos >= 0 && pos < 10) {
    if (DEBUG_OSC_MSG) {
      Serial.print(pos);
      Serial.print(" ");
      Serial.println(intensity);
    }
    ledIntesity[pos] = intensity;
  }
}

void OSCset7Seg(OSCMessage &msg, int addrOffset) {
  if (DEBUG_OSC_MSG) Serial.print("> /nm/set7seg ");
  int pos = msg.getInt(0);
  char letter = (char) msg.getInt(1);
  if (pos >= 0 && pos < 10) {
    if (DEBUG_OSC_MSG) {
      Serial.print(pos);
      Serial.print(" ");
      Serial.println(letter);
    }
    segmentData[pos] = letter;
  }
}

void OSCset7SegAll(OSCMessage &msg, int addrOffset) {
  int pos = msg.getInt(0);
  char letter = (char) msg.getInt(1);
  for (int i = 0; i < 10; i++) {
    segmentData[i] = (char) msg.getInt(i);
  }
}

void sendInputsOSC() {
  OSCBundle bndl  ;
  for (int i = 0; i < 10; i++) {
    if (FADER_VALUES[i] != FADER_VALUES_LAST[i]) {
      bndl.add("/nm/f").add((int) i).add((int) FADER_VALUES[i]);
      FADER_VALUES_LAST[i] = FADER_VALUES[i];
    }
    if (POT0_VALUES[i] != POT0_VALUES_LAST[i]) {
      bndl.add("/nm/p0").add((int) i).add((int) POT0_VALUES[i]);
      POT0_VALUES_LAST[i] = POT0_VALUES[i];
    }
    if (POT1_VALUES[i] != POT1_VALUES_LAST[i]) {
      bndl.add("/nm/p1").add((int) i).add((int) POT1_VALUES[i]);
      POT1_VALUES_LAST[i] = POT1_VALUES[i];
    }
    if (BUTTON0_VALUES[i] != BUTTON0_VALUES_LAST[i]) {
      bndl.add("/nm/b0").add((int) i).add((int) BUTTON0_VALUES[i]);
      BUTTON0_VALUES_LAST[i] = BUTTON0_VALUES[i];
    }
    if (BUTTON1_VALUES[i] != BUTTON1_VALUES_LAST[i]) {
      bndl.add("/nm/b1").add((int) i).add((int) BUTTON1_VALUES[i]);
      BUTTON1_VALUES_LAST[i] = BUTTON1_VALUES[i];
    }

  }
  Udp.beginPacket(serverIP, serverPort);
  bndl.send(Udp);
  Udp.endPacket();
  bndl.empty();
}


void sendInputsAllOSC() {
  if (Ethernet.linkStatus() == LinkON) {
    OSCMessage msg0("/nm/fader");
    for (int i = 0; i < 10; i++) {
      msg0.add((int) FADER_VALUES[i]);
    }
    Udp.beginPacket(serverIP, serverPort);
    msg0.send(Udp);
    Udp.endPacket();
    msg0.empty();

    OSCMessage msg1("/nm/pot0");
    for (int i = 0; i < 10; i++) {
      msg1.add((int) POT0_VALUES[i]);
    }
    Udp.beginPacket(serverIP, serverPort);
    msg1.send(Udp);
    Udp.endPacket();
    msg1.empty();

    OSCMessage msg2("/nm/pot1");
    for (int i = 0; i < 10; i++) {
      msg2.add((int) POT1_VALUES[i]);
    }
    Udp.beginPacket(serverIP, serverPort);
    msg2.send(Udp);
    Udp.endPacket();
    msg2.empty();


    OSCMessage msg3("/nm/button0");
    for (int i = 0; i < 10; i++) {
      msg3.add((int) BUTTON0_VALUES[i]);
    }
    Udp.beginPacket(serverIP, serverPort);
    msg3.send(Udp);
    Udp.endPacket();
    msg3.empty();

    OSCMessage msg4("/nm/button1");
    for (int i = 0; i < 10; i++) {
      msg4.add((int) BUTTON1_VALUES[i]);
    }
    Udp.beginPacket(serverIP, serverPort);
    msg4.send(Udp);
    Udp.endPacket();
    msg4.empty();
  }
}
