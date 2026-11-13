#ifndef HAL_H
#define HAL_H

#include "capteur.h"

void hardware_init();

void sim_calibration();

void capteurs_lire(int brut[NB_capteurs]);
void moteur_g(float u);
void moteur_d(float u);
float encodeur_g();
float encodeur_d();

#endif