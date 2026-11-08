#include "sim.h"
//============================================================
//variable capteurs (simulation)
//============================================================
int test1[NB_capteurs] = {0, 0, 5000,5000, 0, 0}; 
float test2[NB_capteurs] = {0, 0, 500, 500, 0, 0}; 
float test3[NB_capteurs] = {1000, 1000, 0, 0, 0, 0}; 

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
    for (int i = 0; i < NB_capteurs; i++) brut[i] = test1[i];
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