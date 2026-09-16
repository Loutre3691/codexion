#include "codexion.h"

void    free_all(t_coder *coders, t_dongle *dongle, t_monitor *monitor, t_data *data)
{
    free(coders);
    free(dongle);
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
    t_coder     *coder;
    t_dongle    *dongle;
    t_monitor   *monitor;
    int i;

    i = 0;
    monitor = malloc(sizeof(t_monitor));
    coder = calloc(data->number_of_coders, sizeof(t_coder));
    dongle = calloc(data->number_of_coders, sizeof(t_dongle));

    if(!coder || !dongle)
        exit(1);

    init_t_dongle(dongle, data);
    init_t_monitor(monitor, data, coder);
    init_t_coder(data, dongle, coder, monitor);

    while(i < data->number_of_coders)
    {
        pthread_create(&coder[i].thread, NULL, routine_function, &coder[i]);
        i++;
    }
    pthread_create(&monitor->thread, NULL, monitor_routine, monitor);
    join_thread(coder, data);
    destroy_mutex(data, dongle, coder);
    free_all(coder, dongle, monitor, data);
}


