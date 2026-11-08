#include <Arduino.h>
#include "pid.h"
#include "capteur.h"
#include "asserv.h"
#include "sim.h"

void setup() {
  Serial.begin(115200);
  sim_calibration();
  asserv_init();
  sim_lire_capteurs(brut);
  /*Serial.print("linge detecter? "); Serial.println(ligne_detectee(valeur));
  Serial.print("test1 = "); Serial.println(ligne_position(valeur));

  Serial.print("test2 = "); Serial.println(ligne_position(test2));
  Serial.print("test3 = "); Serial.println(ligne_position(test3));*/
}

void loop() {
  Serial.print(">vitesse_g:"); Serial.println(vitesse_g);
  Serial.print(">vitesse_d:"); Serial.println(vitesse_d);
  Serial.print(">consigne_d:");  Serial.println(consigne_d);
  Serial.print(">consigne_g:");  Serial.println(consigne_g);
  Serial.print(">u_g:"); Serial.println(u_g);  
  delay(20);
}

