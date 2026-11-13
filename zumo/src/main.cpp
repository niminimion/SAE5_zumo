#include <Arduino.h>
#include "pid.h"
#include "capteur.h"
#include "asserv.h"
#include "hal.h"
#include "ihm.h"
#include "pin.h"
#include "fsm.h"

volatile Etat etat = ATTENTE;

void mode_calibration (){
    calibration_reset();
    etat = CALIBRATION;
    Serial.println("etat : CALIBRATION");

}


void setup() {
  Serial.begin(115200);
  calibration_reset();
  ihm_init();
  hardware_init();
  if (calibration_charger()){
    etat = PRET;
    Serial.println("Calibration chargee depuis la flash");
  }  
  else{
    etat = ATTENTE;
    Serial.println("Aucune calibration chargee depuis la flash");
  }
  asserv_init();
  calibration_afficher();
}

void loop() {
  Serial.print(">vitesse_g:"); Serial.println(vitesse_g);
  Serial.print(">vitesse_d:"); Serial.println(vitesse_d);
  Serial.print(">consigne_d:");  Serial.println(consigne_d);
  Serial.print(">consigne_g:");  Serial.println(consigne_g);
  Serial.print(">etat:"); Serial.println(etat);
  Serial.print(">u_g:"); Serial.println(u_g);


  EvtBouton evt = bouton_evenement();
  switch (etat) {
    case ATTENTE:
      if (evt == LONG_APPUI)  mode_calibration ();
      break;

    case CALIBRATION:               
      if (evt == RELACHE) {
        // calibration_sauvegarder();
        //calibration_afficher();
        etat = PRET;
        Serial.println("etat : CALIBRATION");
      }
      
      break;

    case PRET:
      if (evt == RELACHE) {
        etat = SUIVI;
        Serial.println("etat : SUIVI");
      }
      if (evt == LONG_APPUI)  mode_calibration ();
      break;

    case SUIVI:
      if (evt == RELACHE) {
        etat = ARRET;
        Serial.println("etat : ARRET");
      }
      break;

    case ARRET:
      if (evt == RELACHE) { 
        etat = PRET;
        Serial.println("etat : PRET");
      }
      if (evt == LONG_APPUI)  mode_calibration ();
      break;
  }

      
  delay(20);
}



