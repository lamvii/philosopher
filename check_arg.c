/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:11:08 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/19 00:38:55 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	arguments_valid(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][++j]))
				return (FAILED);
		}
		if (ft_strlen(av[i]) > 10)
			return (FAILED);
	}
	return (SUCCESSE);
}
