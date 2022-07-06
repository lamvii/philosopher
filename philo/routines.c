/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:40:31 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/06 19:08:48 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eating_routin(t_philo **philo)
{
	pthread_mutex_lock(&((*philo)->next->fork));
	pthread_mutex_lock(&((*philo)->fork));
	pthread_mutex_lock(&((*philo)->info->message));
	printf("%lld: %d has taken forks\n",
		time_after_create((*philo)->time_create), (*philo)->id);
	pthread_mutex_unlock(&((*philo)->info->message));
	(*philo)->last_meal = current_time();
	pthread_mutex_lock(&((*philo)->info->message));
	printf("%lld: %d is eating \n",
		time_after_create((*philo)->time_create), (*philo)->id);
	pthread_mutex_unlock(&((*philo)->info->message));
	usleep((*philo)->info->eat_time * 1000);
	if ((*philo)->required_meals > 0)
		(*philo)->required_meals--;
	pthread_mutex_unlock(&((*philo)->next->fork));
	pthread_mutex_unlock(&((*philo)->fork));
}

void	sleeping_routin(t_philo **philo)
{
	usleep((*philo)->info->sleep_time * 1000);
	pthread_mutex_lock(&((*philo)->info->message));
	printf("%lld: %d is sleeping \n",
		time_after_create((*philo)->time_create), (*philo)->id);
	pthread_mutex_unlock(&((*philo)->info->message));
}

void	thinking_routin(t_philo **philo)
{
	pthread_mutex_lock(&((*philo)->info->message));
	printf("%lld: %d is thinking \n",
		time_after_create((*philo)->time_create), (*philo)->id);
	pthread_mutex_unlock(&((*philo)->info->message));
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
	return (NULL);
}
