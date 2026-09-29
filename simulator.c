#include "codexion.h"

void    free_all(t_coder *coders, t_dongle *dongle, t_monitor *monitor, t_data *data)
{
    free(data->scheduler.list_fifo);
    free(data->scheduler.list_edf);
    free(coders);
    free(dongle);
    free(monitor);
    free(data);
    
}

/*
Boucle pour detruire les mutex et cond 
*/
void    destroy_mutex(t_data *data, t_dongle *dongle,t_coder *coder)
{    
    int i;

    i = 0;
    while(i < data->number_of_coders)
    {
        pthread_mutex_destroy(&dongle[i].mutex);
        pthread_cond_destroy(&dongle[i].cond);
        pthread_mutex_destroy(&coder[i].mutex_last_compil);
        i++;
    }

    pthread_cond_destroy(&coder->monitor->stop_cond);
    pthread_mutex_destroy(&coder->monitor->stop_mutex);
    pthread_mutex_destroy(&coder->monitor->print_mutex);
    pthread_mutex_destroy(&data->scheduler.mutex_compteur);

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
    int         i;
    t_coder     *coder;
    t_dongle    *dongle;
    t_monitor   *monitor;

    i = 0;
    ft_malloc_data(data);
    coder = data->coder;
    monitor = data->monitor;
    dongle = data->dongle;

    init_t_dongle(dongle, data);
    init_t_monitor(monitor, data, coder);
    init_t_coder(data, dongle, coder, monitor);
    init_scheduler(data);

    while(i < data->number_of_coders)
    {
        pthread_create(&coder[i].thread, NULL, routine_function, &coder[i]);
        i++;
    }
    pthread_create(&monitor->thread, NULL, monitor_routine, monitor);
    join_thread(coder, data); // permet d'attendre que tous le monde a fini
    destroy_mutex(data, dongle, coder);
    free_all(coder, dongle, monitor, data);
}


