/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:40:31 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/26 13:26:30 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	my_usleep(long long time_now, long long time_to_sleep)
{
	long long	end;

	end = time_now + time_to_sleep;
	while (current_time() <= end)
		usleep(100);
}

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
	my_usleep(current_time(), (*philo)->info->eat_time);
	if ((*philo)->required_meals >= 0)
		(*philo)->required_meals--;
	pthread_mutex_unlock(&((*philo)->next->fork));
	pthread_mutex_unlock(&((*philo)->fork));
}

void	sleeping_routin(t_philo **philo)
{
	pthread_mutex_lock(&((*philo)->info->message));
	printf("%lld: %d is sleeping \n",
		time_after_create((*philo)->time_create), (*philo)->id);
	pthread_mutex_unlock(&((*philo)->info->message));
	my_usleep(current_time(), (*philo)->info->sleep_time);
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
	philo->time_create = current_time();
	while (1)
	{
		eating_routin(&philo);
		sleeping_routin(&philo);
		thinking_routin(&philo);
	}
	return (NULL);
}
