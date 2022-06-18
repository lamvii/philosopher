/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:07:48 by ael-idri          #+#    #+#             */
/*   Updated: 2022/05/31 22:47:55 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H

# define PHILOSOPHER_H

# define FAILED 0
# define SUCCESSE 1

# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	int				philo_nb;
	int				die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	int				aphilo_is_dead;
	int				philos_full;
}					t_info;

typedef struct s_philo
{
	pthread_t		phi;
	int				id;
	unsigned int	time_create;
	unsigned int	last_meal;
	int				requerted_meals;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_info			*info;
}					t_philo;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);

#endif