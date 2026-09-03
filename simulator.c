#include "codexion.h"

void simulator(t_data *data)
{
    t_coder     *coders;
    t_dongle    *dongles;


    // allouer de la memoire pour le nombre de coder et le nombre de dongle crees
    coders = malloc(sizeof(t_coder) * data->number_of_coders);
    dongles = malloc(sizeof(t_dongle) * data->number_of_coders);

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