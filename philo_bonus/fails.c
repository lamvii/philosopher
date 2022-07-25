/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fails.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:15:18 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/25 18:45:43 by ael-idri         ###   ########.fr       */
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
		if (sem_close((*info)->message))
			printf("error close sem is not a valid semaphore descriptor\n");
		if (sem_close((*info)->die))
			printf("error close sem is not a valid semaphore descriptor\n");
		if (sem_close((*info)->full))
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

	while ((*philo)->next)
	{
		temp = (*philo);
		*philo = (*philo)->next;
		free(temp);
	}
	if (sem_close((*philo)->info->full) != 0)
		printf("error close sem is not a valid semaphore descriptor\n");
	if (sem_close((*philo)->info->die))
		printf("error close sem is not a valid semaphore descriptor\n");
	if (sem_close((*philo)->info->fork))
		printf("error close sem is not a valid semaphore descriptor\n");
	if (sem_close((*philo)->info->message))
		printf("error close sem is not a valid semaphore descriptor\n");
	free((*philo)->info);
	temp = (*philo);
	*philo = (*philo)->next;
	free(temp);
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
