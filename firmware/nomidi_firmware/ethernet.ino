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
