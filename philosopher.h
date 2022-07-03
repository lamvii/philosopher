/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:07:48 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/01 18:29:41 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H

# define PHILOSOPHER_H

# define FAILED 0
# define SUCCESSE 1

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_info
{
	int				philo_nb;
	int				die_time;
	long long		eat_time;
	long long		sleep_time;
	int				aphilo_is_dead;
	int				philos_full;
	pthread_mutex_t	message;
}					t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		phi;
	pthread_mutex_t	fork;
	long long		time_create;
	long long		last_meal;
	int				requerted_meals;
	t_info			*info;
	struct s_philo	*next;
}					t_philo;

//		check_arg.c
int				arguments_valid(char **av);

//		initialise_philos.c
int				initialise_philos(t_philo **philo, int ac, char **av);

//		utils.c
int				ft_strlen(char *s);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
long long		current_time(void);

#endif