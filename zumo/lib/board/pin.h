#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include <stdint.h>
#include "capteur.h"

// TIM1 : PWM moteur A (CH1, CH2)
// TIM4 : PWM moteur B (CH3, CH4)
// TIM2 : encodeur 1      
// TIM3 : encodeur 2
//==========timer==========
#define TIMER_ASSERV  TIM11

//==========pin============
#define BP2            PC13

//==========capteurs============
const uint32_t CAPT[NB_capteurs] = {PA4, PB0, PC1, PC0, PA6, PA7};
//                                  OUT1 OUT2 OUT3 OUT4 OUT5 OUT6

//==========moteurs=============
#define AIN1           PA8
#define AIN2           PA9
#define BIN1           PB9
#define BIN2           PB8 
#define NFAULT         PA10

//==========ENcodeurs============
#define ENC1_A         PA0
#define ENC1_B         PA1
#define ENC2_A         PB4
#define ENC2_B         PB5

//==========OLED=================
#define SDA_OLED       PB3
#define SCL_OLED       PB10

//===========switch=============
#define SW1            PC6
#define BP1            PC8

//===========Potar=============
#define POT1           PC5

//==========Mesure Batterie=====
#define MesBat         PC4

#endif