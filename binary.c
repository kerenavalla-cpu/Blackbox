#include <stdio.h>
#include "binary.h"
void analyse_crash(void)
{
    FILE *f = fopen("crash.bin", "rb");
    if (!f) {
        printf("Aucun fichier crash.bin trouve\n");
        return;
    }

    Frame frame;
    float somme_v = 0.0f;
    float temp_max = 0.0f;
    int n = 0;

    while (fread(&frame, sizeof(Frame) - sizeof(Frame *), 1, f)) {
        somme_v += frame.vitesse;
        if (frame.temperature_moteur > temp_max)
            temp_max = frame.temperature_moteur;
        n++;
    }

    fclose(f);

    if (n > 0) {
        printf("\n=== ANALYSE POST-MORTEM ===\n");
        printf("Vitesse moyenne (10s) : %.2f km/h\n", somme_v / n);
        printf("Temperature max       : %.2f °C\n", temp_max);
    }
}

void dump_memory(BoiteNoire *b)
{
    FILE *f = fopen("crash.bin", "wb");
    if (!f) {
        printf("Erreur ouverture fichier crash.bin\n");
        return;
    }

    Frame *courant = b->debut;
    while (courant != NULL) {
        fwrite(courant, sizeof(Frame) - sizeof(Frame *), 1, f);
        courant = courant->suivant;
    }

    fclose(f);
    printf("Sauvegarde d'urgence effectuee (crash.bin)\n");
}
