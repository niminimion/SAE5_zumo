#include "ihm.h"
#include "pin.h"
#include <Arduino.h>

void ihm_init(){
    pinMode(BP2,INPUT);
    pinMode(BP1,INPUT);   
}

EvtBouton bouton_evenement(){
    static int avant = HIGH;              
    int maintenant = digitalRead(BP2);
    static unsigned long dernier_appui = 0;
    static bool LONG = false;
    EvtBouton evt = AUCUN;

    if (avant == HIGH && maintenant == LOW){
        evt = APPUI;
        dernier_appui = millis();
        LONG = false;
    }
    if (maintenant == LOW && (millis() - dernier_appui) > 3000 && LONG == false ) {
        LONG = true;
        evt = LONG_APPUI;
    }
    if (avant == LOW && maintenant == HIGH && LONG == false) evt = RELACHE;  
    avant = maintenant;

    
    return evt;
}