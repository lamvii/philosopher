/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonnus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:57:07 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/07 17:36:53 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONNUS_H

# define PHILO_BONNUS_H

# define FAILED 	0
# define SUCCESS 	1
# define DIED		2
# define FULL		3

# include <sys/types.h>
# include <pthread.h>
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
	pid_t			pid;
	long long		time_create;
	long long		last_meal;
	int				nb_of_meals;
	t_info			*info;
	struct s_philo	*next;
}					t_philo;

//		check_arg.c
int			arguments_valid(char **av);

//		initialise_philos.c
int			initialise_philos(t_philo **philo, t_info **info,
				int ac, char **av);

//		creat_threads.c
// int			create_threads(t_philo **philo);

//		create_process.c
int			create_process(t_philo **philo);

//		monitor.c
int			monitor(t_philo **philo);

//		routines.c
void		eating_routin(t_philo **philo);
void		sleeping_routin(t_philo **philo);
void		thinking_routin(t_philo **philo);
void		process_routine(t_philo	*philo);

//		fails.c
int			stop_simulation(t_philo **philo);
int			fail_create(t_philo **philo);
int			fail_initialise(t_philo **philo, t_info **info);

//		utils.c
int			ft_strlen(char *s);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	current_time(void);
long long	time_after_create(long long time_create);

#endif // PHILO_BONNUS_H
