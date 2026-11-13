#ifndef FSM_H
#define FSM_H

enum Etat { ATTENTE, CALIBRATION, PRET, SUIVI, ARRET };
extern volatile Etat etat;      

#endif