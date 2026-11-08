#include <Arduino.h>
#include "asserv.h"
#include "capteur.h"
#include "pid.h"
#include "hal.h"

#define TIMER_ASSERV  TIM11 
HardwareTimer *timer = new HardwareTimer(TIMER_ASSERV);

//               {    P     ,      I    ,    D     ,   ts     , integral, erreur precident }
PID pid_g      = {10.0f     , 100.0f    , 0.0f     , 0.005f   , 0       , 0};
PID pid_d      = {10.0f     , 100.0f    , 0.0f     , 0.005f   , 0       , 0};
PID pid_suivre = {0.1f      , 0.0f      , 0.005f   , 0.005f   , 0       , 0};

int vitesse = 300; //vitesse defini par etudiant

int brut[NB_capteurs] = {0, 0, 0, 0, 0, 0};      //tableau valeur brut recu par les capteurs
float valeur[NB_capteurs] = {0, 0, 0, 0, 0, 0}; // tableau pour stocker les valeurs apres calibration

//============================================================
//variable partie moteur
//============================================================
volatile float vitesse_g = 0;    //vitesse du moteur gauche
volatile float vitesse_d = 0;     //vitesse du moteur droit
volatile float u_g = 0;        //puissance du moteur gauche
volatile float u_d = 0;

//============================================================
//variable partie suivre ligne
//============================================================
volatile uint8_t consigne_suivre = 0;
volatile float correction = 0;
volatile float consigne_d;
volatile float consigne_g;

void suivre_ligne(int vitesse, float valeur[NB_capteurs] ){
  float position = ligne_position(valeur);
  correction = pid_calcul(pid_suivre,consigne_suivre,position);
  consigne_d = vitesse + correction;
  consigne_g = vitesse - correction;
}

void asservissement() {
  capteurs_normaliser(brut, valeur);
  suivre_ligne(vitesse,valeur);

  vitesse_g = encodeur_g();
  u_g = pid_calcul(pid_g, consigne_g, vitesse_g);
  moteur_g(u_g);

  vitesse_d = encodeur_d();
  u_d = pid_calcul(pid_d, consigne_d, vitesse_d);
  moteur_d(u_d);
  
}

void asserv_init(){
    timer->setOverflow(200, HERTZ_FORMAT);     // set timer to overflow every 5 ms (200 Hz)
    timer->attachInterrupt(asservissement);   // attach the asservissement function to the timer interrupt
    timer->resume();  
}