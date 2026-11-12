#include "capteur.h"
#include <Arduino.h>
#include <EEPROM.h>

const float seuils =300;

static int cal_min[NB_capteurs];   //valeur min vu
static int cal_max[NB_capteurs];   //valeur max vu

//============================================================
//Stocker les données de calibration dans flash
//============================================================
struct CalibFlash {
  uint32_t magic;           // valeur magique pour vérifier la validité des données
  int min[NB_capteurs];
  int max[NB_capteurs];
};
const uint32_t CALIB_MAGIC = 0x20261111; 

void calibration_sauvegarder(){
  CalibFlash data;
  data.magic = CALIB_MAGIC;
  for (int i = 0; i < NB_capteurs; i++) {
        data.min[i] = cal_min[i];         
        data.max[i] = cal_max[i];          
    }

  EEPROM.put(0, data); 
}

bool calibration_charger() {
    CalibFlash data;                      

    EEPROM.get(0, data);                  // Lire les données de calibration depuis l'EEPROM

    if (data.magic != CALIB_MAGIC) {      // Vérifier la valeur magique pour s'assurer que les données sont valides
        return false;                     
    }

    for (int i = 0; i < NB_capteurs; i++) {
        cal_min[i] = data.min[i];         
        cal_max[i] = data.max[i];
    }
    return true;                          
}

//============================================================
//Calculer la position de la ligne en fonction des valeurs lues par les capteurs
//============================================================
float ligne_position(float valeur[NB_capteurs]){
  static float position_prec = 0;
  float numerateur = 0; // la somme des produits capteur * valeur lue
  float denominateur = 0; // la somme des valeurs lues

  for (int i = 0; i < NB_capteurs; i++) {
   numerateur += capteurs[i] * valeur[i]; // la valeur lue par le capteur i
   denominateur += valeur[i];
  }

  if (denominateur <= seuils) {
    return position_prec; // éviter la division par zéro
  }

  float position = numerateur / denominateur; //pour calculer la position de la ligne
  position_prec = position; 
  return position;
};

//============================================================
//normaliser la valeur de capteur de 0 a 1000
//============================================================
float normaliser(int min, int max, int brut){
  float val_normalise;
  if (max > min){
    val_normalise = (brut - min) * 1000.0f / (max - min);
    if (val_normalise > 1000) val_normalise = 1000;
    if (val_normalise < 0) val_normalise = 0;
    return val_normalise ;
  }
  else return 0 ;
}

void calibration_reset(){
  for (int i = 0; i < NB_capteurs; i++) {
    cal_min[i] = ADC_MAX;
    cal_max[i] = 0;
  }
}

void calibration(int brut[NB_capteurs]){

  for (int i = 0; i < NB_capteurs; i++) {
    if (cal_min[i] > brut[i]) cal_min[i] = brut[i];
    if (cal_max[i] < brut[i]) cal_max[i] = brut[i];
  }
}

void capteurs_normaliser(int brut[NB_capteurs], float valeur[NB_capteurs]){
  for (int i = 0; i < NB_capteurs; i++) {
    valeur[i] = normaliser(cal_min[i],cal_max[i],brut[i]);
  }
}

bool ligne_detectee(float valeur[NB_capteurs]){
  float somme=0;
  for (int i = 0; i < NB_capteurs; i++){
    somme += valeur[i];
  }
  if (somme > seuils) return true;
  else return false;
}

