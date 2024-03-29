#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>

// Librairie : pio lib -g install adafruit/RTClib
// RTClib Library • 2.1.1 • Published on Tue Aug  9 17:19:27 2022
// Ajouter dans platformio.ini : lib_deps = RTClib
// Ajouter éventuellement dans platformio.includes : /home/USERS/PROFS/pcruchet/.platformio/lib/RTClib/src

RTC_DS3231 rtc;
const int CLOCK_INTERRUPT = 23;
//bool alarme = false;

void IRAM_ATTR onAlarme()
{
   // alarme = true;
}



void setup()
{
    Serial.begin(115200);
    Wire.begin();

    if (!rtc.begin()) {
        Serial.println("L'horloge DS3231 ne fonctionne pas !");
    }
    else
    {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // Activer l'interruption
        pinMode(CLOCK_INTERRUPT, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT), onAlarme, FALLING);
        rtc.clearAlarm(1);
        rtc.clearAlarm(2);

        // Configurer l'interruption dans 10 secondes
        if(!rtc.setAlarm1(rtc.now() + TimeSpan(10),DS3231_A1_Second))
            Serial.println("Erreur l'alarme n'est pas enclenchée");
        else
        {
            Serial.println("Une alarme apparaîtra dans 10 secondes");
        }
    }
}

void loop()
{
    if (rtc.alarmFired(1))
    {
        Serial.println("Alarme générée !!!");
        //alarme = false;
        rtc.clearAlarm(1);
        if(!rtc.setAlarm1(rtc.now() + TimeSpan(10),DS3231_A1_Second))
            Serial.println("Erreur l'alarme n'est pas enclenchée");
        else
        {
            Serial.println("Une alarme apparaîtra dans 10 secondes");
        }
    }
}


