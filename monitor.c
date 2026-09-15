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
    t_monitor *monitor;
    monitor = (t_monitor *)arg;
    
    while (monitor->stop_routine == false)
    {
        int i = 0;
        while(i < monitor->data->number_of_coders)
        {
            monitor->deadline_burnout = monitor->coder[i].last_compil + (monitor->data->time_to_burnout * 1000);
            if(get_time_ms() >= monitor->deadline_burnout)
            {
                pthread_mutex_lock(&monitor->print_mutex);
                printf("%lld %d is burnout\n", get_time_ms() - monitor->start_time, i);
                pthread_mutex_unlock(&monitor->print_mutex);

                monitor->stop_routine = true;
            }
            i++;
        }
        usleep(1000); // pause pour laisser un temps off de 0,1 secondes
    }
    return (NULL);
}
