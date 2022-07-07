/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fails.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:15:18 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/07 16:52:41 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonnus.h"

int	exit_philo(t_philo **philo, t_info **info)
{
	t_philo	*temp;

	if (*info)
	{
		if (sem_close((*info)->fork))
			printf("error close sem is not a valid semaphore descriptor\n");
		free(*info);
	}
	while ((*philo))
	{
		temp = (*philo);
		*philo = (*philo)->next;
		free(temp);
	}
	return (1);
}

int	stop_simulation(t_philo **philo)
{
	t_philo	*temp;
	int		philo_nb;

	if (sem_close((*philo)->info->fork))
		printf("error close sem is not a valid semaphore descriptor\n");
	philo_nb = (*philo)->info->philo_nb;
	free((*philo)->info);
	while ((*philo) && philo_nb > 0)
	{
		temp = (*philo);
		*philo = (*philo)->next;
		free(temp);
		philo_nb--;
	}
	return (1);
}

int	fail_initialise(t_philo **philo, t_info **info)
{
	printf("fail initialise, programe will close ..\n");
	return (exit_philo(philo, info));
}

int	fail_create(t_philo **philo)
{
	printf("fail create philo threads, programe will close ..\n");
	return (stop_simulation(philo));
}
