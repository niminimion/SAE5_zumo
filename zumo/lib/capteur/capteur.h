#ifndef CAPTEUR_H
#define CAPTEUR_H
#include <stdint.h> 

const uint8_t NB_capteurs= 6;
const float capteurs[NB_capteurs] = {-2900, -1600, -450, 450, 1600, 2900};
const uint16_t ADC_MAX = 4095;



float ligne_position(float valeur[NB_capteurs]);
float normaliser(int min, int max, int brut);
void calibration_reset();
void calibration(int brut[NB_capteurs]);
void capteurs_normaliser(int brut[NB_capteurs], float valeur[NB_capteurs]);
bool ligne_detectee(float valeur[NB_capteurs]);

void calibration_sauvegarder();
bool calibration_charger();

#endif