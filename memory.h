#ifndef MEMORY_H
#define MEMORY_H

#include <time.h>

/* Structure représentant une trame enregistrée */
typedef struct Frame {
    long timestamp;                 // heure de l'enregistrement
    float vitesse;                  // km/h
    float temperature_moteur;       // °C
    struct Frame *suivant;          // pointeur vers la trame suivante
} Frame;

/* Structure représentant la boîte noire */
typedef struct {
    Frame *debut;   // trame la plus ancienne
    int nb_frames;  // nombre de trames stockées (max 10)
} BoiteNoire;

/* Prototypes des fonctions de gestion mémoire */
void init_boite_noire(BoiteNoire *b);
void enregistrer_cycle(BoiteNoire *b, float vitesse, float temperature, int secondes);
void liberer_boite_noire(BoiteNoire *b);

#endif
