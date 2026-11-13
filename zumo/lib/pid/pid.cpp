#include "pid.h"

void pid_reset(PID &pid){
  pid.integral = 0;
  pid.erreur_prec = 0;

}

float pid_calcul(PID &pid, float consigne, float mesure) {
  float erreur = consigne - mesure;                                     // calcul de l'erreur
  float p = pid.kp * erreur;                                      // calcul de la puissance du moteur
  pid.integral = pid.integral + pid.ki * erreur * pid.ts;         // calcul de l'intégrale de l'erreur
  float d = pid.kd * (erreur - pid.erreur_prec) / pid.ts;          // calcul de la dérivée de l'erreur
  pid.erreur_prec = erreur;                                        // mémorisation de l'erreur précédente 
  if (pid.integral > u_max) pid.integral = u_max;                     // saturation de l'intégrale
  if (pid.integral < u_min) pid.integral = u_min;                     
  float u = p + pid.integral + d;                                     // calcul de la puissance du moteur
  if (u > u_max) u = u_max;                                             // saturation de la puissance du moteur
  if (u < u_min) u = u_min;                                                 // saturation de la puissance
  return u;
}