#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

void init_boite_noire(BoiteNoire *b)
{
    b->debut = NULL;
    b->nb_frames = 0;
}

void enregistrer_cycle(BoiteNoire *b, float vitesse, float temperature, int secondes)
{
    Frame *nouvelle = malloc(sizeof(Frame));
    if (nouvelle == NULL) {
        printf("Erreur allocation memoire\n");
        return;
    }

    nouvelle->timestamp = time(NULL);
    nouvelle->vitesse = vitesse;
    nouvelle->temperature_moteur = temperature;
    nouvelle->suivant = NULL;

    // Cas 1 : liste vide
    if (b->debut == NULL) {
        b->debut = nouvelle;
        b->nb_frames = 1;
        printf("Enregistrement Frame [%d s]...(Memoire:%d/10)\n",
               secondes, b->nb_frames);
        return;
    }

    // Aller à la fin de la liste
    Frame *courant = b->debut;
    while (courant->suivant != NULL) {
        courant = courant->suivant;
    }
    courant->suivant = nouvelle;

    // Cas 2 : mémoire pas encore pleine
    if (b->nb_frames < 10) {
        b->nb_frames++;
    }
    // Cas 3 : mémoire pleine → rotation FIFO
    else {
        Frame *ancienne = b->debut;
        b->debut = ancienne->suivant; // recâbler AVANT free
        free(ancienne);
        printf("Rotation : Frame ancienne ecrasee.\n");
    }

    printf("Enregistrement Frame [%d s]... (Memoire : %d/10)\n",
           secondes, b->nb_frames);
}

void liberer_boite_noire(BoiteNoire *b)
{
    Frame *courant = b->debut;
    while (courant != NULL)
    {
        Frame *tmp = courant;
        courant = courant->suivant;
        free(tmp);
    }
    b->debut = NULL;
    b->nb_frames = 0;
}
