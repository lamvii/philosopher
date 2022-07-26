/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:15:55 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/26 13:53:23 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonnus.h"

void	my_usleep(long long time_now, long long time_to_sleep)
{
	long long	end;

	end = time_now + time_to_sleep;
	while (current_time() <= end)
		usleep(100);
}

void	eating_routin(t_philo **philo)
{
	sem_wait((*philo)->info->fork);
	sem_wait((*philo)->info->fork);
	sem_wait((*philo)->info->message);
	printf("%lld: %d has taken forks\n",
		time_after_create((*philo)->time_create), (*philo)->id);
	sem_post((*philo)->info->message);
	(*philo)->last_meal = current_time();
	sem_wait((*philo)->info->message);
	printf("%lld: %d is eating \n",
		time_after_create((*philo)->time_create), (*philo)->id);
	sem_post((*philo)->info->message);
	my_usleep(current_time(), (*philo)->info->eat_time);
	if ((*philo)->nb_of_meals < (*philo)->info->meals_required)
		(*philo)->nb_of_meals++;
	sem_post((*philo)->info->fork);
	sem_post((*philo)->info->fork);
}

void	sleeping_routin(t_philo **philo)
{
	sem_wait((*philo)->info->message);
	printf("%lld: %d is sleeping \n",
		time_after_create((*philo)->time_create), (*philo)->id);
	sem_post((*philo)->info->message);
	my_usleep(current_time(), (*philo)->info->sleep_time);
}

void	thinking_routin(t_philo **philo)
{
	sem_wait((*philo)->info->message);
	printf("%lld: %d is thinking \n",
		time_after_create((*philo)->time_create), (*philo)->id);
	sem_post((*philo)->info->message);
}

void	process_routine(t_philo	*philo)
{
	philo->time_create = current_time();
	if (pthread_create(&philo->phi, NULL, process_thread, (void *)philo))
	{
		printf("fail create thread\n");
		exit(FAILED);
	}
	while (1)
	{
		eating_routin(&philo);
		sleeping_routin(&philo);
		thinking_routin(&philo);
	}
	exit(0);
}
