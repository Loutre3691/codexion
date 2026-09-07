#include "codexion.h"

void simulator(t_data *data)
{
    t_coder     *coders;
    t_dongle    *dongles;

    // allouer de la memoire pour le nombre de coder et le nombre de dongle crees
    coders = calloc(data->number_of_coders, sizeof(t_coder));
    dongles = calloc(data->number_of_coders, sizeof(t_dongle));

    if(!coders || !dongles)
        exit(1);

    /* 
    boucle sur index i pour creer un thread a chaque id de t_coder
     le thread est deja cree dans la strcut t_coder pour ca 
    quon ne le recreeer pas ici
    il faut creer un mutex par dongle dans la structure t_dongle, chaque dongles
    est partage entre deux coders
    */
    mutex_dongle(dongles, data);
    create_coders(data, dongles, coders);
    join_coders(data, coders);
    destroy_dongles(data, dongles);

    free(coders);
    free(dongles);
}