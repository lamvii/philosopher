/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:07:26 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/21 02:32:19 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_routin(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("thread id: %d is created\n", philo->id);
	// (*philo)->time_create = current_time();
	//take fork of prev philethen your fork
	// look for max thread per processe
	return (NULL);
}

int	creat_threads(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo) && ++i <= (*philo)->info->philo_nb)
	{
		if (pthread_create(&(*philo)->phi, NULL, philo_routin, (void *)*philo))
			return (FAILED);
		*philo = (*philo)->next;
	}
	return (SUCCESSE);
}

int	exit_philo(t_philo **philo)
{
	free((*philo)->info);
	while ((*philo))
	{
		if (pthread_mutex_destroy(&(*philo)->fork))
		{
			pthread_mutex_unlock(&(*philo)->fork);
			pthread_mutex_destroy(&(*philo)->fork);
		}
		*philo = (*philo)->next;
	}
	return (1);
}

int	fail_initialise(t_philo **philo)
{
	printf("fail initialise, programe will close ..\n");
	return (exit_philo(philo));
}

int	fail_create(t_philo **philo)
{
	printf("fail create, programe will close ..\n");
	return (exit_philo(philo));
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = NULL;
	if ((ac == 5 || ac == 6) && arguments_valid(av))
	{
		if (!initialise_philos(&philo, ac, av))
			return (fail_initialise(&philo));
		if (!creat_threads(&philo))
			return (fail_create(&philo));
	}
	else
		printf ("arguments not valid \n");
	sleep(5);
	return (0);
}
