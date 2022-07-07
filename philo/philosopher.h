/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:07:48 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/07 14:43:42 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H

# define PHILOSOPHER_H

# define FAILED 0
# define SUCCESS 1

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
	int				required_meals;
	int				philo_full;
	t_info			*info;
	struct s_philo	*next;
}					t_philo;

//		check_arg.c
int			arguments_valid(char **av);

//		initialise_philos.c
int			initialise_philos(t_philo **philo, t_info **info,
				int ac, char **av);

//		creat_threads.c
int			create_threads(t_philo **philo);

//		routines.c
void		eating_routin(t_philo **philo);
void		sleeping_routin(t_philo **philo);
void		thinking_routin(t_philo **philo);
void		*philo_routin(void	*data);

//		fails.c
int			fail_create(t_philo **philo);
int			fail_initialise(t_philo **philo, t_info **info);

//		utils.c
int			ft_strlen(char *s);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	current_time(void);
long long	time_after_create(long long time_create);

#endif