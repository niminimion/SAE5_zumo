#ifndef CAPTEUR_H
#define CAPTEUR_H

const int NB_capteurs= 6;
const float capteurs[NB_capteurs] = {-2900, -1600, -450, 450, 1600, 2900};

float ligne_position(float test[NB_capteurs]);
#endif