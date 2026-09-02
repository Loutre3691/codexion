#include "codexion.h"

void simulator(t_data *data)
{
    t_coder     *coders;
    t_dongle    *dongles;
    int         i;

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
    i = 0;
    while(i < data->number_of_coders)
    {
        mutex_dongle(dongles, i);
        create_coders(data, i, dongles, coders);
        i++;
    }

    /*
    La deuxieme boucle permet d' attendre que le coders[i].thread termine s
    sa fonction et fait son return
    */
    i = 0;
    while(i < data->number_of_coders)
    {
        pthread_join(coders[i].thread, NULL);
        i++;
    }

    /*
    Boucle pour detruire les mutex des dongles, il est essentiel de creer 
    une nouvelle boucle pour ne pas bloquer les dongles des coders voisin
    qui n'auraient pas finis de travailler
    */
    i = 0;
    while(i < data->number_of_coders)
    {
        pthread_mutex_destroy(&dongles[i].mutex);
        i++;
    }
    
    free(coders);
    free(dongles);
}