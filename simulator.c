#include "codexion.h"

void    free_all(t_coder *coders, t_dongle *dongles, t_monitor *monitor)
{
    free(coders);
    free(dongles);
    free(monitor);
}

void simulator(t_data *data)
{
    t_coder     *coders;
    t_dongle    *dongles;
    t_monitor   *monitor;


    // allouer de la memoire pour le nombre de coder et le nombre de dongle crees
    monitor = malloc(sizeof(t_monitor));
    coders = calloc(data->number_of_coders, sizeof(t_coder));
    dongles = calloc(data->number_of_coders, sizeof(t_dongle));

    if(!coders || !dongles)
        exit(1);

    // init de t_Monito
    init_monitor(monitor, data, coders);

    /* 
    boucle sur index i pour creer un thread a chaque id de t_coder
     le thread est deja cree dans la strcut t_coder pour ca 
    quon ne le recreeer pas ici
    il faut creer un mutex par dongle dans la structure t_dongle, chaque dongles
    est partage entre deux coders
    */
    init_dongle(dongles, data);
    create_coders(data, dongles, coders, monitor);
    // join_coders(data, coders);
    destroy_dongles(data, dongles);

    free_all(coders, dongles, monitor);
}
