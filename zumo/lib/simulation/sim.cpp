#if SIMULATION
#include "sim.h"
#include <Arduino.h>
#include "pin.h"
#include <stdint.h>

//============================================================
//variable capteurs (simulation)
//============================================================
uint32_t a = 0;
uint32_t b = 5000;
int test1[NB_capteurs] = {0, a, 5000,b, 0, 0}; 
int test2[NB_capteurs] = {0, 5000, 5000, 0, 0, 0}; 
int test3[NB_capteurs] = {0, 0, 0, 5000, 5000, 0}; 

int blanc[NB_capteurs] = {500, 400, 400, 300, 210, 270};
int noir[NB_capteurs] = {5000, 4020, 4040, 5300, 6210, 4270};

static float vitesse_sim_g;
static float vitesse_sim_d;

//============================================================
//simulation capteurs
//============================================================
void sim_calibration(){
    calibration_reset();
    calibration(blanc);
    calibration(noir);
}

void capteurs_lire(int brut[NB_capteurs]){
    
        brut[0] = 0;
        brut[1] = a;
        brut[2] = 5000;
        brut[3] = b;
        brut[4] = 0;
        brut[5] = 0;

    
    if (digitalRead(BP2) == 0 ){
        if (a<5000) a+=50;
        if (b>0) b-=50;
    }
    else if (digitalRead(BP2) == 1 ){
        if (b<5000) b+=50;
        if (a>0) a-=50;
        
    }
}

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