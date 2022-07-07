/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:15:55 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/07 17:36:51 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonnus.h"

void	eating_routin(t_philo **philo)
{
	sem_wait((*philo)->info->fork);
	sem_wait((*philo)->info->fork);
	printf("%lld: %d has taken forks\n",
		time_after_create((*philo)->time_create), (*philo)->id);
	(*philo)->last_meal = current_time();
	printf("%lld: %d is eating \n",
		time_after_create((*philo)->time_create), (*philo)->id);
	usleep((*philo)->info->eat_time * 1000);
	sem_post((*philo)->info->fork);
	sem_post((*philo)->info->fork);
}

void	sleeping_routin(t_philo **philo)
{
	usleep((*philo)->info->sleep_time * 1000);
	printf("%lld: %d is sleeping \n",
		time_after_create((*philo)->time_create), (*philo)->id);
}

void	thinking_routin(t_philo **philo)
{
	printf("%lld: %d is thinking \n",
		time_after_create((*philo)->time_create), (*philo)->id);
}

void	process_routine(t_philo	*philo)
{
	philo->time_create = current_time();
	while (1)
	{
		eating_routin(&philo);
		sleeping_routin(&philo);
		thinking_routin(&philo);
	}
	exit(0);
}
