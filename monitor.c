#include "codexion.h"
 
void    ft_print_burnout(t_monitor *monitor, int i)
{
    pthread_mutex_lock(&monitor->print_mutex);
    printf("\033[1;38;2;255;0;0m%lld %d burned out\n", get_time_ms() - monitor->start_time, i);
    pthread_mutex_unlock(&monitor->print_mutex);
    monitor->stop_routine = true;
}

/* Fonction permettant de gerer le burnout et egalement le nbr_of_compile_requiered*/
void    *monitor_routine(void *arg)
{
    t_monitor *monitor;
    bool all_done;

    monitor = (t_monitor *)arg;
    while (monitor->stop_routine == false)
    {
        all_done = true; // supposition tous les coders sont arriver a nb_compile requiered
        int i = 0;
        while(i < monitor->data->number_of_coders)
        {
            pthread_mutex_lock(&monitor->coder[i].mutex_last_compil);
            monitor->deadline_burnout = monitor->coder[i].last_compil + (monitor->data->time_to_burnout * 1000);
            if (get_time_ms() >= monitor->deadline_burnout)
                ft_print_burnout(monitor, i);
            if (monitor->coder[i].nb_compil < monitor->data->number_of_compile_required)
                all_done = false;
            pthread_mutex_unlock(&monitor->coder[i].mutex_last_compil);
            i++;
        }  
        if (all_done == true)
            monitor->stop_routine = true;
        usleep(1000); // pause pour laisser un temps off de 0,1 secondes
    }
    return (NULL);
}
