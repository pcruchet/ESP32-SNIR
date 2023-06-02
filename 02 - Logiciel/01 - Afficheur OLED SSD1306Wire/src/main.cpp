#include <Arduino.h>

#include <SSD1306Wire.h>
// ESP8266 and ESP32 OLED driver for SSD1306 displays
// Librairie : pio lib -g install 2978
// Auteur :ThingPulse, Fabrice Weinberg

#include <OneWire.h>
#include <DallasTemperature.h>
// milesburton/DallasTemperature
// Library • 3.11.0 • Published on Tue Jul  5 11:22:52 2022 : pio lib -g install DallasTemperature
// Arduino Library for Dallas Temperature ICs (DS18B20, DS18S20, DS1822, DS1820, MAX31850)

const int ONE_WIRE_BUS = 18;
const int BP1 = 36;
const int BP2 = 39;
const int BP3 = 34;
const int BP4 = 35;
const int LED = 23;

const int flowPin = 26;         //32-33-25-26  // Broches des capteurs de débit d'eau

unsigned int flowCount; // Compteur de impulsions
float flowRate; // Taux de débit
unsigned long flowMillis; // Temps de la dernière lecture
const int interval = 1000; // Intervalle entre les lectures en ms
const float flowFactor = 4.5; // Facteur de conversion pour le capteur YF-B5


SSD1306Wire display(0x3c,SDA,SCL, GEOMETRY_128_64);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


void MesurerDebit()
{
    flowCount++;
}

void setup()
{
    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "Boitier Pilotage");
    display.display();

    pinMode(BP1,INPUT);
    pinMode(BP2,INPUT);
    pinMode(BP3,INPUT);
    pinMode(BP4,INPUT);
    pinMode(LED,OUTPUT);

    sensors.begin();

    pinMode(flowPin, INPUT);
    flowCount = 0;
    attachInterrupt(digitalPinToInterrupt(flowPin),MesurerDebit, RISING);
    flowMillis = millis();

}
void loop()
{
    if(!digitalRead(BP1))
    {
        display.clear();
        display.drawString(0, 40, "BP1");
        display.display();
    }
    if(!digitalRead(BP2))
    {
        display.clear();
        display.drawString(0, 40, "BP2");
        display.display();
    }
    if(!digitalRead(BP3))
    {
        display.clear();
        display.drawString(0, 40, "BP3");
        display.display();
    }
    if(!digitalRead(BP4))
    {
        display.clear();
        display.drawString(0, 40, "BP4");
        display.display();
    }


    unsigned long currentMillis = millis();
    if (currentMillis - flowMillis >= interval)
    {
        flowRate = ((1000.0 / (currentMillis - flowMillis)) * flowCount) / flowFactor;
        if (flowRate>0)
        {
            display.clear();
            display.drawString(0, 0, "Debit : " + String(flowRate,2));
            display.drawString(0, 20, "Impulsion : " + String(flowCount));
            display.display();

            flowCount = 0;
        }
        flowMillis = currentMillis;
    }

    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);

    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);
    if (tempC != DEVICE_DISCONNECTED_C)
    {
        display.clear();
        display.drawString(0, 0, "Temp : " + String(tempC,2)+ " °");
        display.display();
    }
}
