#ifndef PID_H
#define PID_H

const int u_max = 1000;  // puissance maximale du moteur
const int u_min = -1000; // puissance minimale du moteur

struct PID {         
  float kp;
  float ki;
  float kd;
  float ts;
  float integral;
  float erreur_prec;
};

float pid_calcul(PID &pid, float consigne, float mesure);
void pid_reset(PID &pid);

#endif  