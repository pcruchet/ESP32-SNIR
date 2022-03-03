
/* 
 * File:   Serrure.h
 * Author: fmartin
 *
 * Created on 2 février 2022, 01:01
 */

#ifndef SERRURE_H
#define SERRURE_H

#include <Arduino.h>
#include <ESP32Servo.h>  // Bibliothèque ESP32Servo  #id 4744

class Serrure {
public:
    Serrure(const uint8_t _brocheLedD1 = 13);  // Affectation broche LedD1:GPIO13
    void Deverrouiller();
    void Verrouiller();
    void Debloquer();  
    void Bloquer();   

private:
    Servo leServo;   
    uint8_t brocheLedD1;
    static const int brocheServo = 2;  // Affectation broche servo:GPIO2
};

#endif /* SERRURE_H */

