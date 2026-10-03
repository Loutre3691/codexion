/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-chec <fde-chec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 00:00:00 by fde-chec          #+#    #+#             */
/*   Updated: 2026/10/03 00:00:00 by fde-chec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/* Lit l'heure ACTUELLE (depend de gettimeofday, change a chaque appel)
return les secondes en millisecondes + les microsecondes en millisecondes
*/
long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* transforme un long long (ms) en structure timespec :
tv_sec = division par 1000, tv_nsec = le reste converti en nanosecondes */
struct timespec	get_time_s(long long *deadline)
{
	struct timespec	ts;

	ts.tv_sec = *deadline / 1000;
	ts.tv_nsec = (*deadline % 1000) * 1000000;
	return (ts);
}
