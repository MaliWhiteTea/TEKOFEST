#ifndef TRAFFIC_MONITOR_H
#define TRAFFIC_MONITOR_H

#include <Arduino.h>
#include <Wire.h>

// --- Global değişkenler ---
uint8_t slaveAddr = 0x08;

int guney = 0, kuzey = 0, dogu = 0, bati = 0;
int eskiGuney = -1, eskiKuzey = -1, eskiDogu = -1, eskiBati = -1;

String yogunlukStr = "";
String eskiYogunluk = "";

// --- Fonksiyon prototipleri ---
void beginTrafficMonitor();
void printStatus();
void receiveEvent(int howMany);
void receiveEventStatic(int howMany);

// --- Fonksiyonlar ---

void beginTrafficMonitor() {
  Wire.begin(slaveAddr);
  Wire.onReceive(receiveEventStatic);

}

void printStatus() {
  Serial.print("Güney: "); Serial.print(guney);
  Serial.print(" | Kuzey: "); Serial.print(kuzey);
  Serial.print(" | Doğu: ");  Serial.print(dogu);
  Serial.print(" | Batı: ");  Serial.print(bati);
  Serial.print(" | Yogunluk: "); Serial.println(yogunlukStr);
}

void receiveEventStatic(int howMany) {
  receiveEvent(howMany);
}

void receiveEvent(int howMany) {
  String veri = "";
  while (Wire.available()) {
    char c = Wire.read();
    if (c == '\0' || c == '\r' || c == '\n') continue; 
    veri += c;
  }

  int firstColon  = veri.indexOf(':');
  int secondColon = veri.indexOf(':', firstColon + 1);
  int thirdColon  = veri.indexOf(':', secondColon + 1);

  if (firstColon > 0 && secondColon > firstColon && thirdColon > secondColon) {
    guney = veri.substring(0, firstColon).toInt();
    kuzey = veri.substring(firstColon + 1, secondColon).toInt();
    dogu  = veri.substring(secondColon + 1, thirdColon).toInt();
    bati  = veri.substring(thirdColon + 1).toInt();

    // Doğu-Batı yoğunluk karşılaştırması
    if (dogu > 0 || bati > 0) {
      int fark = dogu - bati;
      if (abs(fark) >= 2) {
        yogunlukStr = (dogu > bati) ? "dogu" : "bati";
      } else {
        yogunlukStr = "";
      }
    } else {
      yogunlukStr = "";
    }

    // Değişiklik kontrolü
    if (guney != eskiGuney || kuzey != eskiKuzey || 
        dogu != eskiDogu || bati != eskiBati || 
        yogunlukStr != eskiYogunluk) {
      printStatus();

      eskiGuney = guney;
      eskiKuzey = kuzey;
      eskiDogu  = dogu;
      eskiBati  = bati;
      eskiYogunluk = yogunlukStr;
    }
  }
}


String getYogunluk() {
  return yogunlukStr;
}
#endif
