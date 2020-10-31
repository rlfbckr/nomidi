#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>
#include <OSCBundle.h>

#include "Type4067Mux.h"
#include "nomidi.h"

boolean DEBUG_OSC_MSG = true;
boolean DEBUG_SERIAL_MSG = true;

IntervalTimer readInputsTimer;
IntervalTimer updateDisplayTimer;
IntervalTimer softPWMTimer;

int t  = 0;

Type4067Mux mux_pot1(POT1_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, POT1_INH);
Type4067Mux mux_pot0(POT0_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, POT0_INH);
Type4067Mux mux_fader(FADER_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, FADER_INH);
Type4067Mux mux_button0(BUTTON0_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, BUTTON0_INH);
Type4067Mux mux_button1(BUTTON1_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, BUTTON1_INH);

EthernetUDP Udp;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFC, 0x88};
IPAddress myIP(10, 0, 0, 123); // contoller
IPAddress serverIP(10, 0, 0, 3); // maxmsp
static int serverPort = 9013;
static int incommingPort = 10013;


void setup() {
  Serial.begin(115200);
  Serial.println("nomidi v");
  Serial.println(  _VERSION_);
  analogReadResolution(12);
  for (int i = 0; i < 10; i++) {
    pinMode(segCathodePins[i], OUTPUT);
    digitalWrite(segCathodePins[i], 0);
    pinMode(ledPins[i] , OUTPUT);
    digitalWrite(ledPins[i], 0);

  }
  for (int i = 0; i < 8; i++) {
    pinMode(segAnodePins[i], OUTPUT);
    digitalWrite(segAnodePins, 0);
  }
  analogReadAveraging(1500);
  initEthernet();
  //readInputsTimer.begin(readInputs, 100);
  updateDisplayTimer.begin(updateSegments, 200);
  softPWMTimer.begin(updateSoftPWM, 160);
}

void loop() {
  readInputs();
  if (t % 10 == 0) {
    sendInputsOSC();
  }

  if (Ethernet.linkStatus() == LinkON) {
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

  t++;
  //delay(50);

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
  if (Ethernet.linkStatus() == LinkON) {
    OSCMessage msg("/nm/fader");
    for (int i = 0; i < 10; i++) {
      msg.add((float) FADER_VALUES[i]);
    }
    Udp.beginPacket(serverIP, serverPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
  }

  if (Ethernet.linkStatus() == LinkON) {
    OSCMessage msg("/nm/pot0");
    for (int i = 0; i < 10; i++) {
      msg.add((float) POT0_VALUES[i]);
    }
    Udp.beginPacket(serverIP, serverPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
  }
  if (Ethernet.linkStatus() == LinkON) {
    OSCMessage msg("/nm/pot1");
    for (int i = 0; i < 10; i++) {
      msg.add((float) POT1_VALUES[i]);
    }
    Udp.beginPacket(serverIP, serverPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
  }


  if (Ethernet.linkStatus() == LinkON) {

    OSCMessage msg("/nm/button0");
    for (int i = 0; i < 10; i++) {
      msg.add((int) BUTTON0_VALUES[i]);
    }
    Udp.beginPacket(serverIP, serverPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
  }
  if (Ethernet.linkStatus() == LinkON) {

    OSCMessage msg("/nm/button1");
    for (int i = 0; i < 10; i++) {
      msg.add((int) BUTTON1_VALUES[i]);
    }
    Udp.beginPacket(serverIP, serverPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
  }

}



void printInputs() {
  if (t % 1000 == 0) {
    Serial.print("POT1 ");
    for (int i = 0; i < 10 ; i++) {
      Serial.print( POT1_VALUES[i] );
      Serial.print(" ");
    }
    Serial.println();

    Serial.print("POT0 ");
    for (int i = 0; i < 10 ; i++) {
      Serial.print( POT0_VALUES[i] );
      Serial.print(" ");
    }
    Serial.println();
    Serial.print("FADER ");
    for (int i = 0; i < 10 ; i++) {
      Serial.print( FADER_VALUES[i] );
      Serial.print(" ");
    }
    Serial.println();
    Serial.print("BUTTON0 ");
    for (int i = 0; i < 10 ; i++) {
      Serial.print( BUTTON0_VALUES[i] );
      Serial.print(" ");
    }
    Serial.println();
    Serial.print("BUTTON1 ");
    for (int i = 0; i < 10 ; i++) {
      Serial.print( BUTTON1_VALUES[i] );
      Serial.print(" ");
    }
    Serial.println();
  }
}
