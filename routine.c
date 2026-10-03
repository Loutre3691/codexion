/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-chec <fde-chec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 00:00:00 by fde-chec          #+#    #+#             */
/*   Updated: 2026/10/03 00:00:00 by fde-chec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/* lit stop_routine sous stop_mutex : la cle n'est gardee
qu'un instant, juste le temps de copier la valeur */
bool	is_stopped(t_coder *coder)
{
	bool	result;

	pthread_mutex_lock(&coder->monitor->stop_mutex);
	result = coder->monitor->stop_routine;
	pthread_mutex_unlock(&coder->monitor->stop_mutex);
	return (result);
}

/* ft_compile prend juste le time_to_compile, met a jour last_compil,
fait attendre avec usleep, et quand c'est ecoule on unlock le dongle
gauche et droit. nb_compil est incremente a la fin (compteur du
nombre de compilations requis) */
void	ft_compile(t_coder *coder)
{
	long long	time_to_compile;
	long long	timer;

	time_to_compile = coder->data->time_to_compile * 1000;
	pthread_mutex_lock(&coder->monitor->print_mutex);
	timer = get_time_ms() - coder->monitor->start_time;
	if (is_stopped(coder))
	{
		put_down_dongles(coder);
		pthread_mutex_unlock(&coder->monitor->print_mutex);
		return ;
	}
	printf("\033[1;38;2;0;250;50m%lld %d is compiling\n\033[00m",
		timer, coder->id + 1);
	pthread_mutex_unlock(&coder->monitor->print_mutex);
	pthread_mutex_lock(&coder->mutex_last_compil);
	coder->last_compil = get_time_ms();
	pthread_mutex_unlock(&coder->mutex_last_compil);
	usleep(time_to_compile);
	put_down_dongles(coder);
	pthread_mutex_lock(&coder->mutex_last_compil);
	coder->nb_compil++;
	pthread_mutex_unlock(&coder->mutex_last_compil);
}

void	ft_debug(t_coder *coder)
{
	long long	time_to_debug;
	long long	timer;

	time_to_debug = coder->data->time_to_debug * 1000;
	pthread_mutex_lock(&coder->monitor->print_mutex);
	timer = get_time_ms() - coder->monitor->start_time;
	if (is_stopped(coder))
	{
		pthread_mutex_unlock(&coder->monitor->print_mutex);
		return ;
	}
	printf("\033[1;38;2;200;0;200m%lld %d is debugging\n\033[00m",
		timer, coder->id + 1);
	pthread_mutex_unlock(&coder->monitor->print_mutex);
	usleep(time_to_debug);
}

void	ft_refactoring(t_coder *coder)
{
	long long	time_to_refactor;
	long long	timer;

	time_to_refactor = coder->data->time_to_refactor * 1000;
	pthread_mutex_lock(&coder->monitor->print_mutex);
	timer = get_time_ms() - coder->monitor->start_time;
	if (is_stopped(coder))
	{
		pthread_mutex_unlock(&coder->monitor->print_mutex);
		return ;
	}
	printf("\033[1;38;2;0;100;255m%lld %d is refactoring\n\033[00m",
		timer, coder->id + 1);
	pthread_mutex_unlock(&coder->monitor->print_mutex);
	usleep(time_to_refactor);
}

/* routine de chaque coder (un thread par coder) :
- cas 1 seul coder : il n'a qu'un dongle, il le prend et attend
  le burnout (impossible de compiler avec un seul dongle)
- decalage de depart : les coders d'id impair attendent 10 ms avant
  leur premiere demande. au debut toutes les deadlines sont egales,
  sans ce decalage les coders prendraient leurs tickets dans l'ordre
  1, 2, 3... et se bloqueraient en file indienne. avec le decalage,
  les coders 1, 3, 5 passent d'abord (ils ne partagent aucun dongle)
  et peuvent compiler en meme temps : on casse la symetrie
- boucle : scheduler (attendre son tour + prendre les dongles),
  compile, debug, refactor, jusqu'a l'arret de la simulation */
void	*routine_function(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->id % 2 == 1)
		usleep(10000);
	if (coder->data->number_of_coders == 1)
	{
		left_dongle_used(coder);
		while (!is_stopped(coder))
			usleep(1000);
		pthread_mutex_unlock(&coder->left_dongle->mutex);
		return (NULL);
	}
	while (!is_stopped(coder))
	{
		scheduler(coder);
		ft_compile(coder);
		if (is_stopped(coder))
			break ;
		ft_debug(coder);
		if (is_stopped(coder))
			break ;
		ft_refactoring(coder);
	}
	return (NULL);
}
