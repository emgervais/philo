/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 21:44:02 by egervais          #+#    #+#             */
/*   Updated: 2023/10/01 21:23:17 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>

# define ERR_AV "Error: wrong argument\n\
        1st argument: number of philosophers\n\
        2nd argument: time to die (in ms)\n\
        3rd argument: time to eat (in ms)\n\
        4th argument: time to sleep (in ms)\n\
        5th argument: number of times each philosopher must eat (optional)\n"
# define MALLOC_FAIL "Error: malloc failed\n"
# define ERR_MUTEX "Error: mutex creation failed\n"
# define ERR_THREAD "Error: thread creation failed\n"
# define ERR_JOIN "Error: thread join failed\n"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t       t1;
	int             id;
	int             eat_count;
	int             status;
	int             eating;
	long long        time_to_die;
	long long        last_meal;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_philo;

typedef struct s_data
{
	int             philo_num;
	int             meals_nb;
	int             dead;
	int             finished;
	t_philo         *philos;
	long long       death_time;
	long long       eat_time;
	long long       sleep_time;
	long long       start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t lock;
} t_data;

bool philo_start(t_data *data);
long atop(char *num);
bool print_error(char *err);
long long	get_time(void);
void ft_usleep(long long time);
bool is_dead(t_philo *philo);
bool init_data(t_data *data, char **av, int ac);
bool init_p(t_data *data);
bool init_philo(t_data *data);
bool init_forks(t_data *data);
void *check(t_data *data);
#endif