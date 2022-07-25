/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:45:40 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/25 17:43:58 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonnus.h"

void	check_philo_full(t_philo *philo)
{
	if (philo->nb_of_meals == philo->info->meals_required)
	{
		sem_post(philo->info->full);
		philo->nb_of_meals++;
	}
}

void	philo_died(t_philo *philo)
{
	if (philo->last_meal == -1
		&& (time_after_create(philo->time_create) > philo->info->die_time))
	{
		sem_wait(philo->info->message);
		printf("%lld: %d died\n",
			time_after_create(philo->time_create), philo->id);
		sem_post(philo->info->die);
	}
	if (philo->last_meal != -1
		&& (current_time() - philo->last_meal) > philo->info->die_time)
	{
		sem_wait(philo->info->message);
		printf("%lld: %d died\n",
			time_after_create(philo->time_create), philo->id);
		sem_post(philo->info->die);
	}
}

void	*process_thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (SUCCESS)
	{
		check_philo_full(philo);
		philo_died(philo);
	}
}
