#include <Arduino.h>
#include "pid.h"
#include "capteur.h"
#include "asserv.h"
#include "hal.h"
#include "sim.h"
#include "ihm.h"
#include "pin.h"
#include "hardware.h"


void setup() {
  Serial.begin(115200);
  calibration_reset();
  ihm_init();
  hardware_init();
  if (calibration_charger())  Serial.println("Calibration chargee depuis la flash");
  else                        Serial.println("Pas de calibration : appuyez sur B1");
  asserv_init();
  calibration_afficher();
}

void loop() {
  /*Serial.print(">vitesse_g:"); Serial.println(vitesse_g);
  Serial.print(">vitesse_d:"); Serial.println(vitesse_d);
  Serial.print(">consigne_d:");  Serial.println(consigne_d);
  Serial.print(">consigne_g:");  Serial.println(consigne_g);
  Serial.print(">u_g:"); Serial.println(u_g);*/

  static int avant = HIGH;              
  int maintenant = digitalRead(BP2);    


  if (avant == HIGH && maintenant == LOW) calibration_reset();

  if (maintenant == LOW) calibration(brut);

  if (avant == LOW && maintenant == HIGH) {                         // relâché
  //calibration_sauvegarder();
  Serial.println("Calibration sauvegardee");
  calibration_afficher();
  }

  avant = maintenant;
    
  delay(20);
}

