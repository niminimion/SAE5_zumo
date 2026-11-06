#include "capteur.h"

const float seuils =300;

float ligne_position(float test[NB_capteurs]){
  static float position_prec = 0;
  float numerateur = 0; // la somme des produits capteur * valeur lue
  float denominateur = 0; // la somme des valeurs lues

  for (int i = 0; i < NB_capteurs; i++) {
   numerateur += capteurs[i] * test[i]; // test[i] est la valeur lue par le capteur i
   denominateur += test[i];
  }

  if (denominateur <= seuils) {
    return position_prec; // éviter la division par zéro
  }

  float position = numerateur / denominateur; //pour calculer la position de la ligne
  position_prec = position; 
  return position;
};