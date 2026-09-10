#include "codexion.h"

/*initialisation des donne de la struc t_Monitor */
void    init_monitor(t_monitor *monitor, t_data *data, t_coder *coders)
{
    monitor->stop_routine = false;
    monitor->data = data;
    monitor->coder = coders;
    pthread_cond_init(&monitor->stop_cond, NULL);
    pthread_mutex_init(&monitor->stop_mutex, NULL);
}