#include "codexion.h"

/*initialisation des donne de la struc t_Monitor */
void    init_t_monitor(t_monitor *monitor, t_data *data, t_coder *coders)
{
    monitor->stop_routine = false;
    monitor->data = data;
    monitor->coder = coders;
    monitor->start_time = get_time_ms();
    monitor->deadline_burnout = 0;
    pthread_cond_init(&monitor->stop_cond, NULL);
    pthread_mutex_init(&monitor->stop_mutex, NULL);
    pthread_mutex_init(&monitor->print_mutex, NULL);
}

/* Fonction permettant de gerer le burnout*/
void    *monitor_routine(void *arg)
{
    t_coder *coder;
    coder = (t_coder *)arg;
    
    long long time_now;
    long long deadline_burnout;
    long long last_time; // temps ecoule depuis derniere action
    
    time_now = get_time_ms();

    coder->monitor->deadline_burnout = coder->last_compil + (coder->data->time_to_burnout * 1000);
    pthread_mutex_lock(&coder->monitor->stop_mutex);
    last_time = time_now - coder->last_compil;
    deadline_burnout = coder->last_compil + (coder->data->time_to_burnout * 1000);
    // recuperation de la structure avec seconde et nano sec de deadline pour la suite
    struct timespec deadline_s = get_time_s(&deadline_burnout);
    /*met le thread en pause. Il se réveille: deadline atteinte, soit autre thread appelle 
    broadcast/signal sur stop_cond. stop_mutex est liberer le temsp de lattente et reverouille
    apres*/
    pthread_cond_timedwait(&coder->monitor->stop_cond, &coder->monitor->stop_mutex, &deadline_s);
    return (NULL);
}
