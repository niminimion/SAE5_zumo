#include <Arduino.h>
#include "asserv.h"
#include "capteur.h"
#include "pid.h"

#define TIMER_ASSERV  TIM11 
HardwareTimer *timer = new HardwareTimer(TIMER_ASSERV);


int test1[NB_capteurs] = {0, 0, 5000,5000, 0, 0}; // tableau pour stocker les valeurs lues par les capteurs
float test2[NB_capteurs] = {0, 0, 500, 500, 0, 0}; // tableau pour stocker les valeurs lues par les capteurs
float test3[NB_capteurs] = {1000, 1000, 0, 0, 0, 0}; // tableau pour stocker les valeurs lues par les capteursb
int vitesse = 300;
//============================================================
//variable partie capteurs
//============================================================
float valeur[NB_capteurs] = {0, 0, 0, 0, 0, 0}; // tableau pour stocker les valeurs lues par les capteurs
int blanc[NB_capteurs] = {500, 400, 400, 300, 210, 270};
int noir[NB_capteurs] = {5000, 4020, 4040, 5300, 6210, 4270};

//============================================================
//variable et fonction partie PID
//============================================================
//          {P    ,      I,    D,   ts  , integral, erreur precident }
PID pid_g = {10.0f, 100.0f, 0.0f, 0.005f, 0, 0};
PID pid_d = {10.0f, 100.0f, 0.0f, 0.005f, 0, 0};

volatile float vitesse_g = 0;    //vitesse du moteur gauche
volatile float vitesse_d = 0;     //vitesse du moteur droit
volatile uint16_t consigne = 800;
volatile int k = 0;            //compteur de tours du moteur
volatile float u_g = 0;        //puissance du moteur gauche

//============================================================
//variable et fonction partie PID
//============================================================
volatile uint8_t consigne_suivre = 0;
volatile float correction = 0;
volatile float consigne_d;
volatile float consigne_g;
PID pid_suivre = {0.1f, 0.0f, 0.005f, 0.005f, 0, 0};

void suivre_ligne(int vitesse, float valeur[NB_capteurs] ){
  float position = ligne_position(valeur);
  correction = pid_calcul(pid_suivre,consigne_suivre,position);
  consigne_d = vitesse + correction;
  consigne_g = vitesse - correction;
}

void asservissement() {
  capteurs_normaliser(test1, valeur);
  suivre_ligne(vitesse,valeur);

  u_g = pid_calcul(pid_g, consigne_g, vitesse_g);
  vitesse_g = vitesse_g + 0.083f * (0.6f * u_g - vitesse_g);   // calcul de la vitesse du moteur gauche

  float u_d = pid_calcul(pid_d, consigne_d, vitesse_d);
  vitesse_d = vitesse_d + 0.083f * (1.0f *u_d - vitesse_d);   // calcul de la vitesse du moteur droit
  
}


void asserv_init(){
    timer->setOverflow(200, HERTZ_FORMAT);     // set timer to overflow every 5 ms (200 Hz)
    timer->attachInterrupt(asservissement);   // attach the asservissement function to the timer interrupt
    timer->resume();  
}