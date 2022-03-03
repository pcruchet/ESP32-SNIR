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

//affectation des E/S GPIO aux L0,L1,L2,L3 du clavier
uint8_t brochesEnLigne[LIGNES] = {32, 33, 25, 26};
//affectation des E/S GPIO aux C0,C1,C2 du clavier
uint8_t brochesEnColonne[COLONNES] = {4, 5, 15};

Keypad clavier(touches,brochesEnLigne,brochesEnColonne,LIGNES,COLONNES);

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    char touche = clavier.getKey();
    if( touche != NO_KEY)
    {
        Serial.println(touche);
    }
}
