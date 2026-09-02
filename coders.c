#include "codexion.h"

void    create_coders(t_data *data, int i, t_dongle *dongles, t_coder *coders)
{
    coders[i].data = data; // recuperation de la struct data dans coders
    coders[i].right_dongle = &dongles[i]; // creation pour chaque id de coder le dongle de droite
    coders[i].left_dongle = &dongles[(i + 1) % data->number_of_coders];
    // creation pour chaque id de coder le dongle de gauche, le modulo permet que le dernier est relie au 1er
    coders[i].id = i; // attribution d'un numero a chaque id de coders
    pthread_create(&coders[i].thread, NULL, routine_function, &coders[i]);
}