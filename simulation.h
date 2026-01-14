#ifndef SIMULATION_H
#define SIMULATION_H

/* Met à jour la vitesse selon l'action utilisateur */
float maj_vitesse(float vitesse, char action);

/* Met à jour la température moteur */
float maj_temperature(float temperature, float vitesse);

#endif
