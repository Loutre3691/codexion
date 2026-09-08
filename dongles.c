#include "codexion.h"

/*
IL est important d'initialiser tous les mutex (les dongles ici) avant de create_coders
*/
void    init_dongle(t_dongle *dongles, t_data *data)
{
    int i;

    i = 0;
    while(i < data->number_of_coders)
    {
        pthread_mutex_init(&dongles[i].mutex, NULL);
        dongles[i].id = i; // pas obligatoire juste pour debug
        dongles[i].is_used = false;
        i++;
    }
}

/*
Boucle pour detruire les mutex des dongles, il est essentiel de creer 
une nouvelle boucle pour ne pas bloquer les dongles des coders voisin
qui n'auraient pas finis de travailler
*/
void    destroy_dongles(t_data *data, t_dongle *dongles)
{    
    int i;

    i = 0;
    while(i < data->number_of_coders)
    {
        pthread_mutex_destroy(&dongles[i].mutex);
        i++;
    }
}