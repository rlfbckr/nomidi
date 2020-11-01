void updateSegments() {
  digitalWrite(segCathodePins[lastSegmentPos], LOW);
  digitalWrite(segCathodePins[segmentPos % segmentMax], HIGH);
  setSegment(segmentData[segmentPos % segmentMax], segmentTic % 8);
  lastSegmentPos = segmentPos % segmentMax;
  segmentTic++;
  if (segmentTic % 8 == 7) {
    segmentPos++;
  }
}

void setSegment(char a, int s) {
  /*

      --a--
     |     |
     f     b
     |     |
      --g--
     |     |
     e     c
     |     |
      --d--

               dp

           7  6  5  4  3  2  1  0
     byte: a  b  c  d  e  f  g  dp

  */
  switch (a) {
    case '0' :  setBits(1, 1, 1, 1, 1, 1, 0, 0, s);
      return;
    case '1' :  setBits(0, 1, 1, 0, 0, 0, 0, 0, s);
      return;
    case '2' :  setBits(1, 1, 0, 1, 1, 0, 1, 0, s);
      return;
    case '3' :  setBits(1, 1, 1, 1, 0, 0, 1, 0, s);
      return;
    case '4' :  setBits(0, 1, 1, 0, 0, 1, 1, 0, s);
      return;
    case '5' :  setBits(1, 0, 1, 1, 0, 1, 1, 0, s);
      return;
    case '6' :  setBits(1, 0, 1, 1, 1, 1, 1, 0, s);
      return;
    case '7' :  setBits(1, 1, 1, 0, 0, 0, 0, 0, s);
      return;
    case '8' :  setBits(1, 1, 1, 1, 1, 1, 1, 0, s);
      return;
    case '9' :  setBits(1, 1, 1, 1, 0, 1, 1, 0, s);
      return;
    case 'A' :  setBits(1, 1, 1, 0, 1, 1, 1, 0, s);
      return;
    case 'a' :  setBits(1, 1, 1, 1, 1, 0, 1, 0, s);
      return;
    case 'B' :  setBits(1, 1, 1, 1, 1, 1, 1, 0, s);
      return;
    case 'b' :  setBits(0, 0, 1, 1, 1, 1, 1, 0, s);
      return;
    case 'C' :  setBits(1, 0, 0, 1, 1, 1, 0, 0, s);
      return;
    case 'c' :  setBits(0, 0, 0, 1, 1, 0, 1, 0, s);
      return;
    case 'D' :  setBits(1, 1, 1, 1, 1, 0, 0, 0, s);
      return;
    case 'd' :  setBits(0, 1, 1, 1, 1, 0, 1, 0, s);
      return;
    case 'E' :  setBits(1, 0, 0, 1, 1, 1, 1, 0, s);
      return;
    case 'e' :  setBits(1, 1, 0, 1, 1, 1, 1, 0, s);
      return;
    case 'F' :  setBits(1, 0, 0, 0, 1, 1, 1, 0, s);
      return;
    case 'f' :  setBits(1, 0, 0, 0, 1, 1, 1, 0, s);
      return;
    case 'G' :  setBits(1, 0, 1, 1, 1, 1, 0, 0, s);
      return;
    case 'g' :  setBits(1, 1, 1, 1, 0, 1, 1, 0, s);
      return;
    case 'H' :  setBits(0, 1, 1, 0, 1, 1, 1, 0, s);
      return;
    case 'h' :  setBits(0, 0, 1, 0, 1, 1, 1, 0, s);
      return;
    case 'I' :  setBits(0, 1, 1, 0, 0, 0, 0, 0, s);
      return;
    case 'i' :  setBits(0, 0, 1, 0, 0, 0, 0, 0, s);
      return;
    case 'J' :  setBits(0, 1, 1, 1, 1, 0, 0, 0, s);
      return;
    case 'j' :  setBits(0, 1, 1, 1, 0, 0, 0, 0, s);
      return;
    case 'K' :  setBits(0, 1, 0, 1, 1, 1, 1, 0, s);
      return;
    case 'k' :  setBits(1, 0, 1, 0, 1, 1, 1, 0, s);
      return;
    case 'L' :  setBits(0, 0, 0, 1, 1, 1, 0, 0, s);
      return;
    case 'l' :  setBits(0, 0, 0, 0, 1, 1, 0, 0, s);
      return;
    case 'M' :  setBits(1, 0, 1, 0, 1, 0, 0, 0, s);
      return;
    case 'm' :  setBits(0, 0, 1, 0, 1, 0, 0, 0, s);
      return;
    case 'N' :  setBits(1, 1, 1, 0, 1, 1, 0, 0, s);
      return;
    case 'n' :  setBits(0, 0, 1, 0, 1, 0, 1, 0, s);
      return;
    case 'O' :  setBits(1, 1, 1, 1, 1, 1, 0, 0, s);
      return;
    case 'o' :  setBits(0, 0, 1, 1, 1, 0, 1, 0, s);
      return;
    case 'P' :  setBits(1, 1, 0, 0, 1, 1, 1, 0, s);
      return;
    case 'p' :  setBits(1, 1, 0, 0, 1, 1, 1, 0, s);
      return;
    case 'Q' :  setBits(1, 1, 0, 1, 0, 1, 1, 0, s);
      return;
    case 'q' :  setBits(1, 1, 1, 0, 0, 1, 1, 0, s);
      return;
    case 'R' :  setBits(1, 1, 0, 0, 1, 1, 0, 0, s);
      return;
    case 'r' :  setBits(0, 0, 0, 0, 1, 0, 1, 0, s);
      return;
    case 'S' :  setBits(1, 0, 1, 1, 0, 1, 1, 0, s);
      return;
    case 's' :  setBits(1, 0, 1, 1, 0, 1, 1, 0, s);
      return;
    case 'T' :  setBits(1, 1, 1, 0, 0, 0, 0, 0, s);
      return;
    case 't' :  setBits(0, 0, 0, 1, 1, 1, 1, 0, s);
      return;
    case 'U' :  setBits(0, 1, 1, 1, 1, 1, 0, 0, s);
      return;
    case 'u' :  setBits(0, 0, 1, 1, 1, 0, 0, 0, s);
      return;
    case 'V' :  setBits(0, 1, 0, 0, 1, 1, 1, 0, s);
      return;
    case 'v' :  setBits(0, 1, 0, 0, 0, 1, 1, 0, s);
      return;
    case 'W' :  setBits(0, 1, 1, 1, 1, 1, 1, 0, s);
      return;
    case 'w' :  setBits(0, 1, 0, 1, 0, 1, 0, 0, s);
      return;
    case 'X' :  setBits(0, 0, 1, 0, 0, 1, 1, 0, s);
      return;
    case 'x' :  setBits(0, 0, 1, 0, 0, 1, 1, 0, s);
      return;
    case 'Y' :  setBits(0, 1, 1, 1, 0, 1, 1, 0, s);
      return;
    case 'y' :  setBits(0, 1, 1, 1, 0, 1, 1, 0, s);
      return;
    case 'Z' :  setBits(1, 1, 0, 1, 1, 0, 1, 0, s);
      return;
    case 'z' :  setBits(1, 1, 0, 1, 1, 0, 1, 0, s);
      return;
    case ',' :  setBits(0, 0, 1, 0, 0, 0, 0, 0, s);
      return;

    case '"' :  setBits(0, 1, 0, 0, 0, 1, 0, 0, s);
      return;

    case '(' :  setBits(1, 0, 0, 1, 1, 1, 0, 0, s);
      return;
    case ')' :  setBits(1, 1, 1, 1, 0, 0, 0, 0, s);
      return;

    case '|' :  setBits(0, 0, 0, 0, 1, 1, 0, 0, s);
      return;

    case '-' :  setBits(0, 0, 0, 0, 0, 0, 1, 0, s);
      return;
    case '_' :  setBits(0, 0, 0, 1, 0, 0, 0, 0, s);
      return;
    default  :  setBits(0, 0, 0, 0, 0, 0, 0, 0, s);
      return;

  }

}


void setBits(int a, int b, int c, int d, int e, int f, int g, int dp, int s) {
  if (s < 8) {
    for (int i = 0; i < 8; i++) {
      if (i != s) { // ???
        digitalWrite(segAnodePins[i], 0);
      }
    }
  }
  switch (s)  {
    case 0: digitalWrite(segAnodePins[0], a); break;
    case 1: digitalWrite(segAnodePins[1], b); break;
    case 2: digitalWrite(segAnodePins[2], c); break;
    case 3: digitalWrite(segAnodePins[3], d); break;
    case 4: digitalWrite(segAnodePins[4], e); break;
    case 5: digitalWrite(segAnodePins[5], f); break;
    case 6: digitalWrite(segAnodePins[6], g); break;
    case 7: digitalWrite(segAnodePins[7], dp); break;
    case 8:
      digitalWrite(segAnodePins[0], a);
      digitalWrite(segAnodePins[1], b);
      digitalWrite(segAnodePins[2], c);
      digitalWrite(segAnodePins[3], d);
      digitalWrite(segAnodePins[4], e);
      digitalWrite(segAnodePins[5], f);
      digitalWrite(segAnodePins[6], g);
      digitalWrite(segAnodePins[7], dp);
      break;
  }

}
