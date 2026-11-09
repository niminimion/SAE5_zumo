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
  asserv_init();
}

void loop() {
  Serial.print(">vitesse_g:"); Serial.println(vitesse_g);
  Serial.print(">vitesse_d:"); Serial.println(vitesse_d);
  Serial.print(">consigne_d:");  Serial.println(consigne_d);
  Serial.print(">consigne_g:");  Serial.println(consigne_g);
  Serial.print(">u_g:"); Serial.println(u_g);

  static int avant = HIGH;              
  int maintenant = digitalRead(BP2);    


  if (avant == HIGH && maintenant == LOW) {
      calibration_reset();
  }

  if (maintenant == LOW) {
      calibration(brut);
  }
  avant = maintenant;
    
  delay(20);
}

