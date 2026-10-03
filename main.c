/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-chec <fde-chec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 00:00:00 by fde-chec          #+#    #+#             */
/*   Updated: 2026/10/03 00:00:00 by fde-chec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	int		arg;
	t_data	*data;

	arg = 1;
	if (argc != 9)
	{
		printf("%s\n", "You must give 8 arguments");
		exit(1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		exit(1);
	sort_parsing(arg, argc, argv, data);
	simulator(data);
	return (0);
}
