#ifndef BLINKALL_H
#define BLINKALL_H

inline void blinkAll(unsigned long duration = 250) { //uint16_t
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, highByte(0x00));
  shiftOut(DATA, CLOCK, MSBFIRST, lowByte(0x01));
  digitalWrite(LATCH, HIGH);
  delay(duration);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, highByte(0x0000));
  shiftOut(DATA, CLOCK, MSBFIRST, lowByte(0x0000));
  digitalWrite(LATCH, HIGH);
  delay(duration);
}






#endif
