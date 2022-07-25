/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:58:33 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/25 18:45:11 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonnus.h"

void	*monitor_full_thread(void *data)
{
	int		i;
	t_philo	*phi;

	phi = (t_philo *)data;
	i = 0;
	while (++i <= phi->info->philo_nb)
		sem_wait(phi->info->full);
	sem_wait(phi->info->message);
	printf("philosophers are full\n");
	sem_post(phi->info->die);
	return (NULL);
}

void	process_monitor(t_philo **philo)
{
	t_philo		*phi;
	pthread_t	thread;

	phi = *philo;
	if (pthread_create(&thread, NULL, monitor_full_thread, (void *)phi))
	{
		printf("fail create thread\n");
		exit(FAILED);
	}
	sem_wait(phi->info->die);
	while (phi)
	{
		kill(phi->pid, 9);
		phi = phi->next;
	}
	exit(SUCCESS);
}

int	monitor(t_philo **philo)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid < 0)
		return (FAILED);
	if (pid == 0)
		process_monitor(philo);
	if (waitpid(pid, &status, 0) != pid)
		printf("fail waiting proc monitor\n");
	if (status)
		return (SUCCESS);
	return (FAILED);
}
