/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:07:26 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/03 20:57:20 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	time_after_create(long long time_create)
{
	return (current_time() - time_create);
}

void	eating_routin(t_philo **philo)
{
	if (((*philo)->last_meal == -1
			&& (time_after_create((*philo)->time_create)
				< (*philo)->info->die_time))
		|| (current_time() - (*philo)->last_meal < (*philo)->info->die_time))
	{
		pthread_mutex_lock(&((*philo)->next->fork));
		pthread_mutex_lock(&((*philo)->fork));
		(*philo)->last_meal = current_time();
		pthread_mutex_lock(&((*philo)->info->message));
		printf("%lld: %d is eating \n",
			time_after_create((*philo)->time_create), (*philo)->id);
		pthread_mutex_unlock(&((*philo)->info->message));
		usleep((*philo)->info->eat_time * 1000);
		pthread_mutex_unlock(&((*philo)->next->fork));
		pthread_mutex_unlock(&((*philo)->fork));
	}
}

void	sleeping_routin(t_philo **philo)
{
	if (((*philo)->last_meal == -1
			&& (time_after_create((*philo)->time_create)
				< (*philo)->info->die_time))
		|| (current_time() - (*philo)->last_meal < (*philo)->info->die_time))
	{
		pthread_mutex_lock(&((*philo)->info->message));
		printf("%lld: %d is sleeping \n",
			time_after_create((*philo)->time_create), (*philo)->id);
		pthread_mutex_unlock(&((*philo)->info->message));
		usleep((*philo)->info->sleep_time * 1000);
	}
}

void	thinking_routin(t_philo **philo)
{
	if (((*philo)->last_meal == -1
			&& (time_after_create((*philo)->time_create)
				< (*philo)->info->die_time))
		|| (current_time() - (*philo)->last_meal < (*philo)->info->die_time))
	{
		pthread_mutex_lock(&((*philo)->info->message));
		printf("%lld: %d is thinking \n",
			time_after_create((*philo)->time_create), (*philo)->id);
		pthread_mutex_unlock(&((*philo)->info->message));
	}
}

void	*philo_routin(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&(philo->info->message));
	printf("thread id: %d is created\n", philo->id);
	pthread_mutex_unlock(&(philo->info->message));
	philo->time_create = current_time();
	while (1)
	{
		eating_routin(&philo);
		sleeping_routin(&philo);
		thinking_routin(&philo);
	}
	//take fork of prev philethen your fork
	// look for max thread per processe
	return (NULL);
}

int	create_threads(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo) && ++i <= (*philo)->info->philo_nb)
	{
		if (pthread_create(&(*philo)->phi, NULL, philo_routin, (void *)*philo))
			return (FAILED);
		*philo = (*philo)->next;
		usleep(100);
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

int	 fail_create(t_philo **philo)
{
	printf("fail create monitoring threads, programe will close ..\n");
	return (exit_philo(philo));
}

void	monitoring(t_philo **philo)
{
	while (1)
	{
		while (*philo)
		{
			if ((*philo)->last_meal == -1 && (time_after_create((*philo)->time_create) > (*philo)->info->die_time))
			{
				pthread_mutex_lock(&((*philo)->info->message));
				printf("%lld: %d died\n", time_after_create((*philo)->time_create), (*philo)->id);
				exit(1);
				// stop_routines(philo);
				// pthread_mutex_lock(&(philo->info->message));
			}
			else if (current_time() - (*philo)->last_meal > (*philo)->info->die_time)
			{
				pthread_mutex_lock(&((*philo)->info->message));
				printf("%lld: %d died\n", time_after_create((*philo)->time_create), (*philo)->id);
				exit(1);
				// pthread_mutex_lock(&(philo->info->message));
			}
		}
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = NULL;
	if ((ac == 5 || ac == 6) && arguments_valid(av))
	{
		if (!initialise_philos(&philo, ac, av))
			return (fail_initialise(&philo));
		if (!create_threads(&philo))
			return (fail_create(&philo));
		monitoring(&philo);
	}
	else
		printf ("arguments not valid \n");
	return (0);
}
