#include "codexion.h"

    /* 
    boucle sur index i pour creer un thread a chaque id de t_coder
    le thread est deja cree dans la struct t_coder pour ca 
    quon ne le recreeer pas ici
     */
void    init_t_coders(t_data *data,  t_dongle *dongles, t_coder *coders, t_monitor *monitor)
{
    int i;

    i = 0;
    while(i < data->number_of_coders)
    {
        coders[i].data = data; // recuperation de la struct data dans coders
        coders[i].right_dongle = &dongles[i]; // creation pour chaque id de coder le dongle de droite
        coders[i].left_dongle = &dongles[(i + 1) % data->number_of_coders];
        // creation pour chaque id de coder le dongle de gauche, le modulo permet que le dernier est relie au 1er
        coders[i].id = i; // attribution d'un numero a chaque id de coders
        coders[i].nb_compil = 0; // init nb_compil et last_compil a 0
        coders[i].last_compil = 0;
        coders[i].monitor = monitor;
        i++;
    }
}

