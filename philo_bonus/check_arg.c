/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:33:18 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/07 14:33:21 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonnus.h"

int	arguments_valid(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (FAILED);
		}
		if (ft_atoi(av[i]) < 0)
			return (FAILED);
	}
	if (ft_atoi(av[1]) <= 0)
	{
		printf("should be at least 1 philo \n");
		return (FAILED);
	}
	return (SUCCESS);
}
