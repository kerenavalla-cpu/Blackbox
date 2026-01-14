#include <stdio.h>
#include "simulation.h"

float maj_vitesse(float vitesse, char action)
{
    if (action == 'A' || action == 'a') {
        vitesse += 5;
    } else if (action == 'F' || action == 'f') {
        vitesse -= 7;
        if (vitesse < 0)
            vitesse = 0;
    }
    return vitesse;
}

float maj_temperature(float temperature, float vitesse)
{
    if (vitesse > 0)
    {
        temperature = temperature+ (0.5f*vitesse)-(0.1*(temperature-20));
    }

    if (temperature < 20)
        temperature = 20;

    return temperature;
}
