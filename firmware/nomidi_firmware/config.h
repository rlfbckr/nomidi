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

/*
   USE_SLIP_SERIAL

   Send and receive OSC date via serial / SLIP Serial
   have a look at examples/nonidi_slipOSC_demo.maxmsp
*/

// #define USE_SLIP_SERIAL

/*
   USE_ETHERNET

   Send and receive OSC date via ethernet
   have a look at examples/nonidi_OSC_demo.maxmsp
*/

#define USE_ETHERNET

/*
   Ethernet IP Configuration
*/

static byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFC, 0x88}; // hardware addres of your device
static IPAddress myIP(10, 0, 0, 123); // ip address of the controller
static IPAddress serverIP(10, 0, 0, 3); // ip addres of your laptop
static int serverPort = 9013;
static int incommingPort = 10013;

boolean DEBUG_OSC_MSG = false;
