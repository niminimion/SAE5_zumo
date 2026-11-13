#ifndef IHM_H
#define IHM_H

void ihm_init();

enum EvtBouton { AUCUN, APPUI, RELACHE , LONG_APPUI}; 
EvtBouton bouton_evenement();

#endif