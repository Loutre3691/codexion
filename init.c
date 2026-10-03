/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-chec <fde-chec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 00:00:00 by fde-chec          #+#    #+#             */
/*   Updated: 2026/10/03 00:00:00 by fde-chec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/* initialisation des donnees de la struct t_monitor */
void	init_t_monitor(t_monitor *monitor, t_data *data, t_coder *coder)
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
boucle sur index i pour initialiser chaque t_coder (le thread est deja
cree dans la struct t_coder, on ne le recree pas ici) :
- right_dongle : le dongle de meme id que le coder
- left_dongle : le suivant, le modulo relie le dernier coder au 1er
- nb_compil et last_compil sont initialises (burnout/EDF)
*/
void	init_t_coder(t_data *data, t_dongle *dongle, t_coder *coder,
			t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < data->number_of_coders)
	{
		coder[i].data = data;
		coder[i].right_dongle = &dongle[i];
		coder[i].left_dongle = &dongle[(i + 1) % data->number_of_coders];
		coder[i].id = i;
		coder[i].nb_compil = 0;
		coder[i].last_compil = monitor->start_time;
		coder[i].monitor = monitor;
		pthread_mutex_init(&coder[i].mutex_last_compil, NULL);
		i++;
	}
}

/*
IL est important d'initialiser tous les mutex et les cond (les dongles ici)
avant de create_coders (l'id des dongles n'est pas obligatoire, pour debug)
*/
void	init_t_dongle(t_dongle *dongle, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_coders)
	{
		pthread_mutex_init(&dongle[i].mutex, NULL);
		pthread_cond_init(&dongle[i].cond, NULL);
		dongle[i].heap.ids = calloc(2, sizeof(int));
		if (!dongle[i].heap.ids)
			exit(1);
		dongle[i].id = i;
		dongle[i].is_used = false;
		dongle[i].last_used = 0;
		i++;
	}
}

void	init_scheduler(t_data *data)
{
	data->scheduler.ticket_counter = 0;
	pthread_mutex_init(&data->scheduler.mutex_counter, NULL);
}

void	ft_malloc_data(t_data *data)
{
	data->coder = calloc(data->number_of_coders, sizeof(t_coder));
	data->monitor = malloc(sizeof(t_monitor));
	data->dongle = calloc(data->number_of_coders, sizeof(t_dongle));
	if (!data->monitor || !data->dongle || !data->coder)
		exit(1);
}
