#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>
#include <OSCBundle.h>

#include "Type4067Mux.h"
#include "nomidi.h"

boolean DEBUG_OSC_MSG = false;
boolean DEBUG_SERIAL_MSG = false;

IntervalTimer readInputsTimer;
IntervalTimer updateDisplayTimer;
IntervalTimer softPWMTimer;

int t  = 0;

Type4067Mux mux_pot1(POT1_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, POT1_INH);
Type4067Mux mux_pot0(POT0_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, POT0_INH);
Type4067Mux mux_fader(FADER_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, FADER_INH);
Type4067Mux mux_switch(SWITCH_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, SWITCH_INH);
Type4067Mux mux_switch2(SWITCH2_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, SWITCH2_INH);

EthernetUDP Udp;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFC, 0x88};
IPAddress myIP(10, 0, 0, 123); // contoller
IPAddress serverIP(10, 0, 0, 3); // maxmsp
static int serverPort = 9003;
static int incommingPort = 10001;


void setup() {


  Serial.begin(115200);
  Serial.println("hi all");
  analogReadResolution(12);
  for (int i = 0; i < 10; i++) {
    pinMode(SEG_K[i], OUTPUT);
    digitalWrite(SEG_K[i], 0);
    pinMode(LED[i] , OUTPUT);
    digitalWrite(LED[i], 0);

  }
  for (int i = 0; i < 8; i++) {
    pinMode(SEG[i], OUTPUT);
    digitalWrite(SEG[i], 0);
  }
  initEthernet();
  // readInputsTimer.begin(readInputs, 1000);
  updateDisplayTimer.begin(updateSegments, 160);
  softPWMTimer.begin(updateSoftPWM, 60);
}

void loop() {
  readInputs();
  if (t % 100 == 0) {
    //sendInputsOSC();
  }
  
  if (Ethernet.linkStatus() == LinkON) {
    OSCMessage msgIn;
    int msg_size;
    if ((msg_size = Udp.parsePacket()) > 0) {
      while (msg_size--)
        msgIn.fill(Udp.read());
      if (!msgIn.hasError()) {
        msgIn.route("/nm/set7seg", OSCset7Seg);

      }
    }
  }

  t++;
  //delay(50);

}
void OSCset7Seg(OSCMessage &msg, int addrOffset) {
  Serial.print("> /nm/set7seg ");
  int pos = msg.getInt(0);
  char letter = (char) msg.getInt(1);
  if (pos >= 0 && pos < 10) {
    Serial.print(pos);
    Serial.print(" ");
    Serial.println(letter);
    segmentData[pos] = letter;
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
    Serial.print("SWITCH ");
    for (int i = 0; i < 10 ; i++) {
      Serial.print( SWITCH_VALUES[i] );
      Serial.print(" ");
    }
    Serial.println();
    Serial.print("SWITCH2 ");
    for (int i = 0; i < 10 ; i++) {
      Serial.print( SWITCH2_VALUES[i] );
      Serial.print(" ");
    }
    Serial.println();
  }
}
