#include "codexion.h"

void create_coders(t_data *data)
{
    t_coder *coders;
    int i;

    // allouer de la memoire pour le nombre de coder
    coders = malloc(sizeof(t_coder) * data->number_of_coders);

    if(!coders)
        exit(1);
    
    // boucle sur index i pour creer un thread a chaque id de t_coder
    // le thread est deja cree dans la strcut t_coder pour ca 
    // quon ne le recreeer pas ici
    i = 0;
    
    while(i < data->number_of_coders)
    {
        coders[i].id = i;
        pthread_create(&coders[i].thread, NULL, routine_fonction, &coders[i]);
        i++;
    }

    /*
    La deuxieme boucle permet d' attendre que le coders[i].thread termine s
    sa fonction et fait son return*/
    i = 0;
    while(i < data->number_of_coders)
    {
        pthread_join(coders[i].thread, NULL);
        i++;
    }
    free(coders);
}