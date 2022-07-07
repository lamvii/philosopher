/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:58:33 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/07 17:10:47 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonnus.h"

int	monitor(t_philo **philo)
{
	t_philo	*phi;

	phi = *philo;
	while (phi)
	{
		if (phi->pid != waitpid(phi->pid, NULL, 0))
		{
			printf("wait of child is failed\n");
			return (FAILED);
		}
		phi = phi->next;
	}
	return (SUCCESS);
}
