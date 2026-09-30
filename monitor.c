#include "codexion.h"

/* Parcourt tous les coders : renvoie false des qu'un coder n'a pas
atteint le nombre de compilations requis, true si tous l'ont atteint */
bool	all_coders_done(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->data->number_of_coders)
	{
		pthread_mutex_lock(&monitor->coder[i].mutex_last_compil);
		if (monitor->coder[i].nb_compil
			< monitor->data->number_of_compile_required)
		{
			pthread_mutex_unlock(&monitor->coder[i].mutex_last_compil);
			return (false);
		}
		pthread_mutex_unlock(&monitor->coder[i].mutex_last_compil);
		i++;
	}
	return (true);
}

bool    ft_print_burnout(t_monitor *monitor, int i)
{
    pthread_mutex_lock(&monitor->coder[i].mutex_last_compil);
    monitor->deadline_burnout = monitor->coder[i].last_compil + (monitor->data->time_to_burnout);
    if (get_time_ms() >= monitor->deadline_burnout)
    {
        pthread_mutex_lock(&monitor->print_mutex);
        printf("\033[1;38;2;255;0;0m%lld %d burned out\n", get_time_ms() - monitor->start_time, i+1);
        monitor->stop_routine = true;
        pthread_mutex_unlock(&monitor->print_mutex);
       
        pthread_mutex_unlock(&monitor->coder[i].mutex_last_compil);
        return(true);
    }
    pthread_mutex_unlock(&monitor->coder[i].mutex_last_compil);
    return(false);
}

/* Surveille les coders : s'arrete au premier burnout,
ou quand tous les coders ont fini leurs compilations */
void	*monitor_routine(void *arg)
{
	t_monitor	*monitor;
	int			i;

	monitor = (t_monitor *)arg;
	while (monitor->stop_routine == false)
	{
		i = 0;
		while (i < monitor->data->number_of_coders)
		{
			if (ft_print_burnout(monitor, i))
				return (NULL);
			i++;
		}
		if (all_coders_done(monitor))
		{
			pthread_mutex_lock(&monitor->print_mutex);
			monitor->stop_routine = true;
			pthread_mutex_unlock(&monitor->print_mutex);
		}
		usleep(1000);
	}
	return (NULL);
}
