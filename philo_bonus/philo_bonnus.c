/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonnus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:47:33 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/06 20:07:23 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonnus.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_info	*info;

	philo = NULL;
	info = NULL;
	if ((ac == 5 || ac == 6) && arguments_valid(av))
	{
		if (!initialise_philos(&philo, &info, ac, av))
			return (fail_initialise(&philo, &info));
		if (!create_process(&philo))
			return (fail_create(&philo));
		// if (monitoring(&philo))
		// 	return (1);
	}
	else
		printf ("wach nta 7mar \n");
}