#include <Arduino.h>
#include "pid.h"
#define TIMER_ASSERV  TIM16     

//          {P    ,      I,    D,   ts  , integral, erreur precident }
PID pid_g = {10.0f, 100.0f, 0.0f, 0.005f, 0, 0};
PID pid_d = {10.0f, 100.0f, 0.0f, 0.005f, 0, 0};

volatile float vitesse_g = 0;    //vitesse du moteur gauche
volatile float vitesse_d = 0;     //vitesse du moteur droit
volatile float consigne = 800;
volatile int k = 0;            //compteur de tours du moteur
volatile float u_g = 0;              //puissance du moteur gauche

void asservissement() {
  if ((k / 400) % 2 == 0) consigne = 400;
  else                    consigne = 200;

  /*float*/ u_g = pid_calcul(pid_g, consigne, vitesse_g);
  vitesse_g = vitesse_g + 0.083f * (0.6f * u_g - vitesse_g);   // calcul de la vitesse du moteur gauche

  float u_d = pid_calcul(pid_d, consigne, vitesse_d);
  vitesse_d = vitesse_d + 0.083f * (1.0f *u_d - vitesse_d);   // calcul de la vitesse du moteur droit
  k++; 
}

HardwareTimer *timer = new HardwareTimer(TIMER_ASSERV);

void setup() {
  Serial.begin(115200);
  timer->setOverflow(200, HERTZ_FORMAT);     // set timer to overflow every 5 ms (200 Hz)
  timer->attachInterrupt(asservissement);    // attach the asservissement function to the timer interrupt
  timer->resume();                           // start the timer
}

void loop() {

  Serial.print(">vitesse_g:"); Serial.println(vitesse_g);
  Serial.print(">vitesse_d:"); Serial.println(vitesse_d);
  Serial.print(">consigne:");  Serial.println(consigne);
  Serial.print(">u_g:"); Serial.println(u_g);
  delay(20);
}

