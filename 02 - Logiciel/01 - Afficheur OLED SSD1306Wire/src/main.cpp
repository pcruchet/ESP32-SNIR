#include <Arduino.h>

#include <SSD1306Wire.h>
// ESP8266 and ESP32 OLED driver for SSD1306 displays
// Librairie : pio lib -g install 2978
// Auteur :ThingPulse, Fabrice Weinberg

SSD1306Wire display(0x3c,SDA,SCL, GEOMETRY_128_64);
void setup()
{
    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "Hello world");
    display.display();
}
void loop()
{

}
