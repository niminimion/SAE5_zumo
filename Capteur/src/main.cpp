#include <Arduino.h>
#include "capteur.h"

float valeur[NB_capteurs] = {0, 0, 0, 0, 0, 0}; // tableau pour stocker les valeurs lues par les capteurs
int blanc[NB_capteurs] = {500, 400, 400, 300, 210, 270};
int noir[NB_capteurs] = {5000, 4020, 4040, 5300, 6210, 4270};

void setup() {
  Serial.begin(9600);
  delay(1000);

  int test1[NB_capteurs] = {0, 0, 5000,5000, 0, 0}; // tableau pour stocker les valeurs lues par les capteurs
  float test2[NB_capteurs] = {0, 0, 500, 500, 0, 0}; // tableau pour stocker les valeurs lues par les capteurs
  float test3[NB_capteurs] = {1000, 1000, 0, 0, 0, 0}; // tableau pour stocker les valeurs lues par les capteurs


  calibration_reset();
  calibration(blanc);
  calibration(noir);
  capteurs_normaliser(test1, valeur);


  Serial.print("linge detecter? "); Serial.println(ligne_detectee(valeur));
  Serial.print("test1 = "); Serial.println(ligne_position(valeur));


  Serial.print("test2 = "); Serial.println(ligne_position(test2));
  Serial.print("test3 = "); Serial.println(ligne_position(test3));
}

void loop() {
  
}

