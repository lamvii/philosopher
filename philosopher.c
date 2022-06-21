/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:07:26 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/21 21:37:31 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

unsigned int	time_after_create(unsigned int time_create)
{
	return (current_time() - time_create);
}

void	eating_routin(t_philo **philo)
{
	pthread_mutex_lock(&((*philo)->next->fork));
	pthread_mutex_lock(&((*philo)->fork));
	(*philo)->last_meal = time_after_create((*philo)->time_create);
	// pthread_mutex_lock(&((*philo)->info->message));
	printf("%d: %d is eating \n", (*philo)->last_meal, (*philo)->id);
	// pthread_mutex_unlock(&((*philo)->info->message));
	usleep((*philo)->info->eat_time * 1000);
	pthread_mutex_unlock(&((*philo)->next->fork));
	pthread_mutex_unlock(&((*philo)->fork));
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
		// pthread_mutex_lock(&(philo->info->message));
		printf("%d: %d is sleeping \n", time_after_create(philo->time_create), philo->id);
		// pthread_mutex_unlock(&(philo->info->message));
		usleep(philo->info->sleep_time * 1000);
		// pthread_mutex_lock(&(philo->info->message));
		printf("%d: %d is thinking \n", time_after_create(philo->time_create), philo->id);
		// pthread_mutex_unlock(&(philo->info->message));
	}
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

int	create_monitoring_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo && ++i <= philo->info->philo_nb)
	{
		if (pthread_create(&philo->phi, NULL, philo_monitoring_thread, (void *)philo))
			return (FAILED);
		philo = philo->next;
		usleep(100);
	}
	return (SUCCESSE);
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

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = NULL;
	if ((ac == 5 || ac == 6) && arguments_valid(av))
	{
		if (!initialise_philos(&philo, ac, av))
			return (fail_initialise(&philo));
		if (!create_monitoring_threads(philo))
			return (fail_create(&philo));
	}
	else
		printf ("arguments not valid \n");
	sleep(100000);
	return (0);
}
