#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "simulation.h"
#include "binary.h"

int main(void)
{
    BoiteNoire b;
    float vitesse = 0.0f;
    float temperature = 20.0f;
    char action;
    int secondes = 1;
    init_boite_noire(&b);

    printf("=== BlackBox - Simulation demarree ===\n");

    while (1) {
        printf("\n[A]ccelerer | [F]reiner : ");
        scanf(" %c", &action);

        vitesse = maj_vitesse(vitesse, action);
        temperature = maj_temperature(temperature, vitesse);

        enregistrer_cycle(&b, vitesse, temperature, secondes);

        printf("Vitesse : %.1f km/h | Temperature : %.1f °C\n",
               vitesse, temperature);

        /* Conditions d'arrêt */
        if (vitesse == 0) {
            printf("Arret du vehicule detecte.\n");
            dump_memory(&b);
            analyse_crash();
            break;
        }

        if (temperature > 110) {
            printf("SURCHAUFFE ! Explosion moteur.\n");
            dump_memory(&b);
            analyse_crash();
            break;
        }
        secondes++;
    }

    liberer_boite_noire(&b);
    return 0;
}
