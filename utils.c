/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:11:27 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/21 01:23:50 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

unsigned int	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (FAILED);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_isdigit(int c)
{
	if ((c <= '9' && c >= '0'))
		return (1);
	else
		return (0);
}

int	ft_strlen(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	int		r;
	char	*ptr;

	i = 0;
	s = 1;
	r = 0;
	ptr = (char *)str;
	while (ptr[i] == 32 || (ptr[i] >= 9 && ptr[i] <= 13))
		i++;
	if (ptr[i] == '-' || ptr[i] == '+')
	{
		if (ptr[i] == '-')
			s = s * (-1);
		i++;
	}
	while (ptr[i] >= '0' && ptr[i] <= '9' )
	{
		r = r * 10 + ptr[i] - 48;
		i++;
	}
	return (s * r);
}
