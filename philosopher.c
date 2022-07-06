/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:07:26 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/06 12:30:27 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	stop_routines(t_philo **philo)
{
	t_philo	*temp;
	int		philo_nb;

	philo_nb = (*philo)->info->philo_nb;
	free((*philo)->info);
	while ((*philo) && philo_nb > 0)
	{
		if (pthread_mutex_destroy(&(*philo)->fork))
		{
			pthread_mutex_unlock(&(*philo)->fork);
			pthread_mutex_destroy(&(*philo)->fork);
		}
		temp = (*philo);
		*philo = (*philo)->next;
		free(temp);
		philo_nb--;
	}
	return (1);
}

int	monitoring(t_philo **philo)
{
	while (*philo)
	{
		if ((*philo)->requerted_meals == 0 && (*philo)->philo_full == 0)
		{
			(*philo)->info->philos_full++;
			(*philo)->philo_full = 1;
			if ((*philo)->info->philos_full == (*philo)->info->philo_nb)
			{
				pthread_mutex_lock(&((*philo)->info->message));
				printf("%lld: philosophers are full\n", time_after_create((*philo)->time_create));
				return (stop_routines(philo));
			}
		}
		if ((*philo)->last_meal == -1 && (time_after_create((*philo)->time_create) > (*philo)->info->die_time))
		{
			pthread_mutex_lock(&((*philo)->info->message));
			printf("%lld: %d died\n", time_after_create((*philo)->time_create), (*philo)->id);
			return (stop_routines(philo));
		}
		else if ((*philo)->last_meal != -1 && (current_time() - (*philo)->last_meal) > (*philo)->info->die_time)
		{
			pthread_mutex_lock(&((*philo)->info->message));
			printf("%lld: %d died\n", time_after_create((*philo)->time_create), (*philo)->id);
			return (stop_routines(philo));
		}
		(*philo) = (*philo)->next;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_info	*info;

	philo = NULL;
	info = NULL;
	if ((ac == 5 || ac == 6) && arguments_valid(av))
	{
		// if (!initialise_philos(&philo, &info, ac, av))
		// 	return (fail_initialise(&philo, &info));
		// if (!create_threads(&philo))
		// 	return (fail_create(&philo));
		// if (monitoring(&philo))
		// 	return (1);
	}
	else
		printf ("wach nta 7mar \n");
	return (0);
}
