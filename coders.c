#include "codexion.h"

void    create_coders(t_data *data,  t_dongle *dongles, t_coder *coders)
{
    int i;
    
    i = 0;
    /* 
    boucle sur index i pour creer un thread a chaque id de t_coder
    le thread est deja cree dans la strcut t_coder pour ca 
    quon ne le recreeer pas ici
     */
    while(i < data->number_of_coders)
    {
        coders[i].data = data; // recuperation de la struct data dans coders
        coders[i].right_dongle = &dongles[i]; // creation pour chaque id de coder le dongle de droite
        coders[i].left_dongle = &dongles[(i + 1) % data->number_of_coders];
        // creation pour chaque id de coder le dongle de gauche, le modulo permet que le dernier est relie au 1er
        coders[i].id = i; // attribution d'un numero a chaque id de coders
        coders[i].nb_compil = 0; // init nb_compil et last_compil a 0
        coders[i].last_compil = 0;
        pthread_create(&coders[i].thread, NULL, routine_function, &coders[i]);
        i++;
    }

}

/*
La deuxieme boucle permet d' attendre que le coders[i].thread termine s
sa fonction et fait son return
*/

void    join_coders(t_data *data, t_coder *coders)
{
    int i;

    i = 0;
    while(i < data->number_of_coders)
    {
        pthread_join(coders[i].thread, NULL);
        i++;
    }
}