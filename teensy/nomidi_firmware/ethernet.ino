void initEthernet() {
  Ethernet.begin(mac, myIP);
  Udp.begin(incommingPort);
  printEthernetStats();
}



void printEthernetStats() {
  Serial.print(millis());
  Serial.print(" ");
  if (Ethernet.linkStatus() == Unknown) {
    Serial.println("> Link status unknown. Link status detection is only available with W5200 and W5500.");
  }
  else if (Ethernet.linkStatus() == LinkON) {
    Serial.println("> Link status: On");
  }
  else if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("> Link status: Off");
  }
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("> Ethernet shield was not found.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5100) {
    Serial.println("> W5100 Ethernet controller detected.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5200) {
    Serial.println("> W5200 Ethernet controller detected.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5500) {
    Serial.println("> W5500 Ethernet controller detected.");
  } else {
    Serial.println("> no Ethernet");
    
  }
}
