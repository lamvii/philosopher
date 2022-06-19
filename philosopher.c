/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:07:26 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/19 01:00:27 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*pthread_handler(t_philo **philo)
{
	(*philo)->time_create = current_time();
	//take fork of prev philethen you fork
}

void	creat_threads(t_philo **philo)
{
	int	i;

	i = 0;
	while (++i <= (*philo)->info->philo_nb)
		pthread_create(&(*philo)->phi, NULL, pthread_handler, philo);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = NULL;
	if ((ac == 5 || ac == 6) && arguments_valid(av))
	{
		if (!initialise_philos(&philo, ac, av))
			exit_philo(&philo);
		creat_threads(&philo);
	}
	else
		printf ("arguments not valid \n");
	return (1);
}
