#include <Arduino.h>
#include <NeoPixelBus.h>  //pio lib -g install 547

const uint16_t NB_PIXELS = 4;
const uint8_t BROCHE_RGB = 19;
const uint8_t COULEUR_DE_SATURATION = 128;

NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> ruban(NB_PIXELS, BROCHE_RGB);

RgbColor ROUGE(COULEUR_DE_SATURATION, 0, 0);
RgbColor VERT(0, COULEUR_DE_SATURATION, 0);
RgbColor BLEU(0, 0, COULEUR_DE_SATURATION);
RgbColor BLANC(COULEUR_DE_SATURATION);
RgbColor NOIR(0);

HslColor HSL_ROUGE(ROUGE);
HslColor HSL_VERT(VERT);
HslColor HSL_BLEU(BLEU);
HslColor HSL_BLANC(BLANC);
HslColor HSL_NOIR(NOIR);

void setup()
{
    Serial.begin(115200);
    while (!Serial);
    Serial.println();
    Serial.println("Initialisation...");

    ruban.Begin();
    ruban.Show();
    Serial.println("Ruban Led lancé...");
    Serial.println();
}


void loop()
{
    Serial.println("Couleurs : Rouge, Vert, Bleu, Blanc...");

    ruban.SetPixelColor(0, ROUGE);
    ruban.SetPixelColor(1, VERT);
    ruban.SetPixelColor(2, BLEU);
    ruban.SetPixelColor(3, BLANC);
    ruban.Show();

    delay(5000);

    Serial.println("Extinction...");

    for(int indice = 0 ; indice < NB_PIXELS ; indice ++)
        ruban.SetPixelColor(indice, NOIR);
    
    ruban.Show();

    delay(5000);

    Serial.println("Couleurs HSL : Rouge, Vert, Bleu, Blanc...");

    ruban.SetPixelColor(0, HSL_ROUGE);
    ruban.SetPixelColor(1, HSL_VERT);
    ruban.SetPixelColor(2, HSL_BLEU);
    ruban.SetPixelColor(3, HSL_BLANC);
    ruban.Show();

    delay(5000);

    Serial.println("Extinction HSL...");

    for(int indice = 0 ; indice < NB_PIXELS ; indice ++)
        ruban.SetPixelColor(indice, HSL_NOIR);
    
    ruban.Show();

    delay(5000);
}
