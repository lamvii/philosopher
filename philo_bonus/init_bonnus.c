/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonnus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:43:04 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/25 18:04:19 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonnus.h"

t_info	*initialise_info(t_info **info, int _meals, char **av)
{
	*info = malloc(sizeof(t_info));
	if (!(*info))
		return (NULL);
	(*info)->philo_nb = ft_atoi(av[1]);
	(*info)->die_time = ft_atoi(av[2]);
	(*info)->eat_time = ft_atoi(av[3]);
	(*info)->sleep_time = ft_atoi(av[4]);
	(*info)->meals_required = _meals;
	sem_unlink("fork");
	(*info)->fork = sem_open("fork", O_CREAT | O_EXCL, 0777, ft_atoi(av[1]));
	if ((*info)->fork == SEM_FAILED)
		return (NULL);
	sem_unlink("print");
	(*info)->message = sem_open("print", O_CREAT | O_EXCL, 0777, 1);
	if ((*info)->message == SEM_FAILED)
		return (NULL);
	sem_unlink("die");
	(*info)->die = sem_open("die", O_CREAT | O_EXCL, 0777, 0);
	if ((*info)->die == SEM_FAILED)
		return (NULL);
	sem_unlink("full");
	(*info)->full = sem_open("full", O_CREAT | O_EXCL, 0777, 0);
	if ((*info)->full == SEM_FAILED)
		return (NULL);
	return (*info);
}

t_philo	*new_philo(int id, t_info **info)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = id;
	new->pid = -2;
	new->time_create = 0;
	new->last_meal = -1;
	new->nb_of_meals = 0;
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
	if (ac == 6)
		_meals = ft_atoi(av[5]);
	if (!initialise_info(info, _meals, av))
		return (FAILED);
	while (++id <= ft_atoi(av[1]))
	{
		new = new_philo(id, info);
		if (!new)
			return (FAILED);
		add_philo_back(new, philo);
	}
	return (SUCCESS);
}
