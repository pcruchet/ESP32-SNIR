#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include <RTClib.h>
// Librairie : pio lib -g install adafruit/RTClib
// RTClib Library • 2.1.1 • Published on Tue Aug  9 17:19:27 2022
// Ajouter éventuellement dans platformio.includes : /home/USERS/PROFS/pcruchet/.platformio/lib/RTClib/src
// Documentation : https://adafruit.github.io/RTClib/html/index.html

#include <SSD1306Wire.h>
// ESP8266 and ESP32 OLED driver for SSD1306 displays
// Librairie : pio lib -g install 2978
// Auteur :ThingPulse, Fabrice Weinberg

#include <Arduino.h>
#include <Keypad.h>
// Keypad
// Installation : pio lib -g install 165
// Auteurs : Mark Stanley, Alexander Brevig

static const uint8_t LIGNES = 4;
static const uint8_t COLONNES = 3;
char touches[LIGNES * COLONNES] = {
    '1', '2', '3',
    '4', '5', '6',
    '7', '8', '9',
    '*', '0', '#'
};

// Clavier connecteur en haut
//affectation des E/S GPIO aux L0,L1,L2,L3 du clavier
uint8_t brochesEnLigne[LIGNES] = {26,25,33,32};
//affectation des E/S GPIO aux C0,C1,C2 du clavier
uint8_t brochesEnColonne[COLONNES] = {15, 5, 4};

Keypad clavier(touches,brochesEnLigne,brochesEnColonne,LIGNES,COLONNES);

RTC_DS3231 rtc;
const int CLOCK_INTERRUPT = 23;

const int BP1 = 39;
const int BP2 = 34;
const int BP3 = 35;

const int LED1 = 13;
const int LED2 = 12;


enum MODE_FONCTIONNEMENT
{
    NORMAL,
    REGLAGE_HEURE,
    REGLAGE_MINUTE,
    ENREGISTREMENT_ACTUEL,
    REGLAGE_ALARME1,
    REGLAGE_ALARME2,
    FIN
};

MODE_FONCTIONNEMENT modeCourant;

SSD1306Wire display(0x3c,SDA,SCL, GEOMETRY_128_64);

String chaineLue = "00" ;

String int2string(int val)
{
    String retour;
    retour += static_cast<char>('0' + val/10);
    retour += static_cast<char>('0' + val%10);

    return retour;
}

void IRAM_ATTR onAlarme()
{
}

void IRAM_ATTR onBP1()
{
    modeCourant = static_cast<MODE_FONCTIONNEMENT>((modeCourant + 1) %  FIN) ;
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
        DateTime actuel = rtc.now();

        display.init();
        display.flipScreenVertically();
        display.setFont(ArialMT_Plain_10);
        char horodatage[] = "DD/MM/YYYY hh:mm:ss";
        display.drawString(0, 0, String(actuel.toString(horodatage)));
        display.display();

        // Activer l'interruption
        pinMode(CLOCK_INTERRUPT, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT), onAlarme, FALLING);
        rtc.clearAlarm(1);
        rtc.clearAlarm(2);

        // Configurer l'interruption dans 10 secondes
        if(!rtc.setAlarm1(rtc.now() + TimeSpan(1),DS3231_A1_Second))
            Serial.println("Erreur l'alarme n'est pas enclenchée");
        else
        {
            Serial.println("Une alarme apparaîtra dans 10 secondes");
        }
    }

    pinMode(BP1,INPUT);
    attachInterrupt(digitalPinToInterrupt(BP1), onBP1, FALLING);
    pinMode(LED1,OUTPUT);
    digitalWrite(LED1,LOW);
}



void loop()
{

    String heure;
    String minute;

    if (rtc.alarmFired(1))
    {
        Serial.println("Alarme générée !!!");
        rtc.clearAlarm(1);
        if(!rtc.setAlarm1(rtc.now() + TimeSpan(1),DS3231_A1_Second))
        {
            Serial.println("Erreur l'alarme n'est pas enclenchée");
        }
        else
            Serial.println("Une alarme apparaîtra dans 10 secondes");

        char horodatage[] = "DD/MM/YYYY hh:mm:ss";
        DateTime actuel = rtc.now();



        display.clear();
        switch(modeCourant)
        {
        case NORMAL:
            display.drawString(0, 0, String(actuel.toString(horodatage)));
            chaineLue = int2string(actuel.hour());
            break;
        case REGLAGE_HEURE:
            heure = chaineLue;
            display.drawString(0,15,"Heure : " + heure);
            break;
        case REGLAGE_MINUTE:
            minute = chaineLue;
            display.drawString(0,15,"Minute : " + minute);
            break;
        case ENREGISTREMENT_ACTUEL:
            actuel = DateTime(actuel.year(),actuel.month(),actuel.day(),heure.toInt(),minute.toInt());
            rtc.adjust(actuel);
            break;
        case REGLAGE_ALARME1:
            display.drawString(0,15,"Alarme 1 :");
            break;
        case REGLAGE_ALARME2:
            display.drawString(0,15,"Alarme 2 :");
            break;
        default :
            break;
        }

        display.display();
    }

    char touche = clavier.getKey();
    if( touche != NO_KEY)
    {
        Serial.println(touche);
        chaineLue[0] = chaineLue[1];
        chaineLue[1] = touche;


    }
}


