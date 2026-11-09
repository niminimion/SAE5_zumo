#if !SIMULATION

#include "hardware.h"
#include "pin.h"
#include <Arduino.h>

void hardware_init(){
    analogReadResolution(12);
    //initlisation de capteurs
    for (int i = 0; i < NB_capteurs; i++) pinMode(CAPT[i],INPUT);
}

void capteurs_lire(int brut[NB_capteurs]){
    for (int i = 0; i < NB_capteurs; i++) {
        brut[i] = analogRead(CAPT[i]);
    }
}


static float vitesse_sim_g;
static float vitesse_sim_d;

//============================================================
//simulation moteur & endodeur
//============================================================
void moteur_g(float u){
    vitesse_sim_g = vitesse_sim_g + 0.083f * (0.6f * u - vitesse_sim_g);
}

void moteur_d(float u){
    vitesse_sim_d = vitesse_sim_d + 0.083f * (1.0f * u - vitesse_sim_d);
}

float encodeur_g(){
    return vitesse_sim_g;
}

float encodeur_d(){
    return vitesse_sim_d;
}


#endif
