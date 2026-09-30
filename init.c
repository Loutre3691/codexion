#include "codexion.h"

/*initialisation des donne de la struc t_Monitor */
void    init_t_monitor(t_monitor *monitor, t_data *data, t_coder *coder)
{
    monitor->stop_routine = false;
    monitor->data = data;
    monitor->coder = coder;
    monitor->start_time = get_time_ms();
    monitor->deadline_burnout = 0;
    pthread_cond_init(&monitor->stop_cond, NULL);
    pthread_mutex_init(&monitor->stop_mutex, NULL);
    pthread_mutex_init(&monitor->print_mutex, NULL);
}

/* 
boucle sur index i pour creer un thread a chaque id de t_coder
le thread est deja cree dans la struct t_coder pour ca 
quon ne le recreeer pas ici
    */
void    init_t_coder(t_data *data,  t_dongle *dongle, t_coder *coder, t_monitor *monitor)
{
    int i;

    i = 0;
    while(i < data->number_of_coders)
    {
        coder[i].data = data; // recuperation de la struct data dans coders
        coder[i].right_dongle = &dongle[i]; // creation pour chaque id de coder le dongle de droite
        coder[i].left_dongle = &dongle[(i + 1) % data->number_of_coders];
        // creation pour chaque id de coder le dongle de gauche, le modulo permet que le dernier est relie au 1er
        coder[i].id = i; // attribution d'un numero a chaque id de coders
        coder[i].nb_compil = 0; // init nb_compil et last_compil a 0
        coder[i].last_compil = monitor->start_time;
        coder[i].monitor = monitor;
        pthread_mutex_init(&coder[i].mutex_last_compil, NULL);
        i++;
    }
}

/*
IL est important d'initialiser tous les mutex et les cond (les dongles ici) avant de create_coders
*/
void    init_t_dongle(t_dongle *dongle, t_data *data)
{
    int i;

    i = 0;
    while(i < data->number_of_coders)
    {
        pthread_mutex_init(&dongle[i].mutex, NULL);
        pthread_cond_init(&dongle[i].cond, NULL);
        dongle[i].id = i; // pas obligatoire juste pour debug
        dongle[i].is_used = false;
        dongle[i].last_used = 0;
        i++;
    }
}

void    init_scheduler(t_data *data)
{
    data->scheduler.heap.size = 0;
    data->scheduler.ticket_counter = 0;

    pthread_mutex_init(&data->scheduler.mutex_compteur, NULL);
    data->scheduler.heap.ids = calloc(data->number_of_coders,sizeof(int));
    if(!data->scheduler.heap.ids)
        exit(1);
}

void    ft_malloc_data(t_data *data)
{
    data->coder = calloc(data->number_of_coders, sizeof(t_coder));
    data->monitor = malloc(sizeof(t_monitor));
    data->dongle = calloc(data->number_of_coders, sizeof(t_dongle));
    if(!data->monitor || !data->dongle || !data->coder)
        exit(1);
}
