/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonnus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:57:07 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/06 19:49:12 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONNUS_H

# define PHILO_BONNUS_H

# define FAILED 	0
# define SUCCESS 	1
# define DIED		2
# define FULL		3

# include <pthread.h>
# include <sys/types.h>
# include <semaphore.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_info
{
	sem_t		*fork;
	int			philo_nb;
	int			die_time;
	long long	eat_time;
	long long	sleep_time;
	int			meals_required;
}				t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		phi;
	long long		time_create;
	long long		last_meal;
	int				nb_of_meals;
	t_info			*info;
	struct s_philo	*next;
}					t_philo;

#endif // PHILO_BONNUS_H
