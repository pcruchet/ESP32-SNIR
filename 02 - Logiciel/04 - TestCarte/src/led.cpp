/*
 * File:   Led.cpp
 * Author: philippe Simier Touchard Washington
 *
 * Created on 14 février 2022, 15:40
 */

#include "led.h"

// Constructeur de Led
Led::Led(word _numPixels):
NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0800KbpsMethod>(_numPixels, PIN_RGB)
{
    Begin();
}


Led::~Led() {
}

/**
 * Allume la led avec la couleur demandée
 * @param couleur RgbColor une couleur
 */

void Led::allumer(const RgbColor &couleur, word id){
    SetPixelColor(id, couleur);
    Show();
}

/**
 * Eteint la led
 */
void Led::eteindre(word id){
    SetPixelColor(id, RgbColor(0,0,0));
    Show();
}




