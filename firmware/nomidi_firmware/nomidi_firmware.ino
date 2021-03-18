#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>
#include <OSCBundle.h>
#include <Chrono.h>
/*
   Tennsy 4.1
   600 Mhz

*/



#include "MUX74HC4067.h"
#include "nomidi.h"

boolean DEBUG_OSC_MSG = false;
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

//Type4067Mux mux_pot1(POT1_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, POT1_INH);
//Type4067Mux mux_pot0(POT0_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, POT0_INH);
//Type4067Mux mux_fader(FADER_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, FADER_INH);
//Type4067Mux mux_button0(BUTTON0_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, BUTTON0_INH);
//Type4067Mux mux_button1(BUTTON1_X, INPUT, ANALOG, ADDR_A, ADDR_B, ADDR_C, ADDR_D, BUTTON1_INH);

EthernetUDP Udp;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFC, 0x88};
IPAddress myIP(10, 0, 0, 123); // contoller
IPAddress serverIP(10, 0, 0, 3); // e.g maxmsp
static int serverPort = 9013;
static int incommingPort = 10013;


void setup() {
  Serial.begin(115200);
  Serial.print("NOMIDI v");
  Serial.println(  _VERSION_);
  analogReadResolution(12);

  mux_pot1.signalPin(POT1_X, INPUT, ANALOG);
  mux_pot0.signalPin(POT0_X, INPUT, ANALOG);
  mux_fader.signalPin(FADER_X, INPUT, ANALOG);
  mux_button0.signalPin(BUTTON0_X, INPUT, ANALOG);
  mux_button1.signalPin(BUTTON1_X, INPUT, ANALOG);
  for (int i = 0; i < 10; i++) {
    pinMode(segCathodePins[i], OUTPUT);
    digitalWrite(segCathodePins[i], 0);
    pinMode(ledPins[i] , OUTPUT);
    digitalWrite(ledPins[i], 0);

  }
 // pinMode(BUTTON0_X, INPUT);
  //pinMode(BUTTON1_X, INPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(segAnodePins[i], OUTPUT);
    digitalWrite(segAnodePins, 0);
  }
  analogReadAveraging(100);
  initEthernet();

  strncpy(segmentData, "softmachin", 10);

  //readInputsTimer.begin(readInputs, 10000);
  updateDisplayTimer.begin(updateSegments, 20);
  softPWMTimer.begin(updateSoftPWM, 100);
}

void loop() {
  if (millis() > 4000 && millis() < 7000) {
    strncpy(segmentData, "~~~~~~~~~~", 10);
  }
  if (millis() > 7000 && millis() < 8000) {
    strncpy(segmentData, "          ", 10);
  }

  if (readInputsChrono.hasPassed(10) ) {
    readInputsChrono.restart();
    readInputs();

  }
  if (sendOSC.hasPassed(30) ) {
    sendOSC.restart();
    sendInputsOSC();
  }

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
}
