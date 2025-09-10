#include <stdint.h>
#include "sistem.h"
#ifndef ANIMATIONS_H
#define ANIMATIONS_H



inline void bastanSona(unsigned long delayTime = 250) {
  uint16_t veri = 0x0001;  // en sağdaki bit

  for (int i = 0; i < 15; i++) {
    veriGonder(veri);      // 16 bit veriyi 595'e gönder
    veri <<= 1;            // bir bit sola kaydır
    delay(delayTime);      // bekle
  }
}

inline void renkleriSirala(unsigned long delayTime = 250) {
  uint16_t kirmizi = 0b0000100100100100;
  uint16_t sari = 0b0001001001001000;
  uint16_t yesil = 0b0010010010010000;
  uint16_t yayakirmizi = 0b0000000000000001;
  uint16_t yayayesil = 0b0000000000000010;

  veriGonder(kirmizi);
  delay(delayTime);
  veriGonder(sari);
  delay(delayTime);
  veriGonder(yesil);
  delay(delayTime);
  veriGonder(yayakirmizi);
  delay(delayTime);  
  veriGonder(yayayesil);
  delay(delayTime);    
 


}








#endif