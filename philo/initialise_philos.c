/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:08:20 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/06 19:06:53 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_info	*initialise_info(t_info **info, char **av)
{
	*info = malloc(sizeof(t_info));
	if (!(*info) || pthread_mutex_init(&((*info)->message), NULL))
		return (NULL);
	(*info)->philo_nb = ft_atoi(av[1]);
	(*info)->die_time = ft_atoi(av[2]);
	(*info)->eat_time = ft_atoi(av[3]);
	(*info)->sleep_time = ft_atoi(av[4]);
	(*info)->aphilo_is_dead = 0;
	(*info)->philos_full = 0;
	return (*info);
}

t_philo	*new_philo(int id, int _meals, t_info **info)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new || pthread_mutex_init(&(new->fork), NULL))
		return (NULL);
	new->id = id;
	new->time_create = 0;
	new->last_meal = -1;
	new->required_meals = _meals;
	new->philo_full = 0;
	new->info = *info;
	new->next = NULL;
	return (new);
}

t_philo	*last_philo(t_philo	*philo)
{
	while (philo->next)
		philo = philo->next;
	return (philo);
}

void	add_philo_back(t_philo *new, t_philo **philo)
{
	t_philo	*last;

	if (!(*philo))
		*philo = new;
	else
	{
		last = last_philo(*philo);
		last->next = new;
	}
}

int	initialise_philos(t_philo **philo, t_info **info, int ac, char **av)
{
	int		id;
	t_philo	*new;
	int		_meals;

	id = 0;
	_meals = -1;
	if (!initialise_info(info, av))
		return (FAILED);
	if (ac == 6)
		_meals = ft_atoi(av[5]);
	while (++id <= ft_atoi(av[1]))
	{
		new = new_philo(id, _meals, info);
		if (!new)
			return (FAILED);
		add_philo_back(new, philo);
	}
	last_philo(*philo)->next = *philo;
	return (SUCCESS);
}
