#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>

// Librairie : pio lib -g install adafruit/RTClib
// RTClib Library • 2.1.1 • Published on Tue Aug  9 17:19:27 2022
// Ajouter dans platformio.ini : lib_deps = RTClib
// Ajouter dans platformio.includes : /home/USERS/PROFS/pcruchet/.platformio/lib/RTClib/src

RTC_DS3231 rtc;

void setup() {
  Serial.begin(115200);
  Wire.begin();


  if (! rtc.begin()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);
}
