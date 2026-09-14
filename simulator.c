#include "codexion.h"

void    free_all(t_coder *coders, t_dongle *dongles, t_monitor *monitor, t_data *data)
{
    free(coders);
    free(dongles);
    free(monitor);
    free(data);
}


/* attend que chaque thread ait fini (return) avant de continuer,
pour ne pas detruire/free de la memoire encore utilisee par un thread actif */

void    join_thread(t_coder *coders, t_data *data)
{
    int i;
    
    i = 0;

    while(i < data->number_of_coders)
    {
        pthread_join(coders[i].thread, NULL);
        i++;
    }
    pthread_join(coders->monitor->thread, NULL);
}

void simulator(t_data *data)
{
    t_coder     *coders;
    t_dongle    *dongles;
    t_monitor   *monitor;
    int i;

    i = 0;
    monitor = malloc(sizeof(t_monitor));
    coders = calloc(data->number_of_coders, sizeof(t_coder));
    dongles = calloc(data->number_of_coders, sizeof(t_dongle));

    if(!coders || !dongles)
        exit(1);

    init_t_dongle(dongles, data);
    init_t_monitor(monitor, data, coders);
    init_t_coders(data, dongles, coders, monitor);

    while(i < data->number_of_coders)
    {
        pthread_create(&coders[i].thread, NULL, routine_function, &coders[i]);
        i++;
    }
    pthread_create(&monitor->thread, NULL, monitor_routine, monitor);
    join_thread(coders, data);
    destroy_dongles(data, dongles);
    free_all(coders, dongles, monitor, data);
}
