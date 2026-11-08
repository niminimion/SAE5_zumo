#ifndef ASSERV_H
#define ASSERV_H

#include "capteur.h"

extern volatile float vitesse_g;
extern volatile float vitesse_d;
extern volatile float consigne_g;
extern volatile float consigne_d;
extern volatile float correction;
extern volatile float u_g;  
extern int brut[NB_capteurs];


void asserv_init();

#endif