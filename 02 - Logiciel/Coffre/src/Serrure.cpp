/* 
 * File:   Serrure.cpp
 * Author: fmartin
 * 
 * Created on 2 février 2022, 01:01
 */

#include "Serrure.h"

Serrure::Serrure(const uint8_t _brocheLedD1) :
brocheLedD1(_brocheLedD1) 
{
    pinMode(brocheLedD1, OUTPUT);   // configuration broche Led D1 en sortie

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    leServo.setPeriodHertz(50); //  configuration periode 50 Hz pour le  servo
    leServo.attach(brocheServo, 1000, 2000); // affectation broche 5 pour commande servo
}

void Serrure::Deverrouiller() {
    digitalWrite(brocheLedD1, LOW);  // Eteindre Led D1
}

void Serrure::Verrouiller() {
    digitalWrite(brocheLedD1, HIGH);  // Allumer Led D1
}

void Serrure::Bloquer() {
    leServo.write(180); // commande servo à 180 °
}

void Serrure::Debloquer() { // commande servo à 0 °
    leServo.write(0);
}