#include "sim.h"
//============================================================
//variable capteurs (simulation)
//============================================================
int test1[NB_capteurs] = {0, 0, 5000,5000, 0, 0}; 
float test2[NB_capteurs] = {0, 0, 500, 500, 0, 0}; 
float test3[NB_capteurs] = {1000, 1000, 0, 0, 0, 0}; 

int blanc[NB_capteurs] = {500, 400, 400, 300, 210, 270};
int noir[NB_capteurs] = {5000, 4020, 4040, 5300, 6210, 4270};

void sim_calibration(){
    calibration_reset();
    calibration(blanc);
    calibration(noir);
}

void sim_lire_capteurs(int brut[NB_capteurs]){
    for (int i = 0; i < NB_capteurs; i++) brut[i] = test1[i];
}