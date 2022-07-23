/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:07:26 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/23 18:09:24 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
		if (!create_threads(&philo))
			return (fail_create(&philo));
		if (!monitoring(&philo))
			return (0);
	}
	else
	{
		printf ("wach nta 7mar \n");
		return (1);
	}
	return (0);
}
