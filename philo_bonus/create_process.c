/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:34:42 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/19 15:12:35 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonnus.h"

int	create_process(t_philo **philo)
{
	pid_t	pid;
	t_philo	*phi;

	phi = *philo;
	while (phi)
	{
		pid = fork();
		if (pid < 0)
			return (FAILED);
		if (pid == 0)
			process_routine(phi);
		phi->pid = pid;
		phi = phi->next;
	}
	return (SUCCESS);
}
