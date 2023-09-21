/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 21:44:02 by egervais          #+#    #+#             */
/*   Updated: 2023/09/20 19:46:41 by egervais         ###   ########.fr       */
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
	pthread_t		t2;
	int             id;
	int             eat_count;
	int             status;
	int             eating;
	uint64_t        time_to_die;
	uint64_t        last_meal;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_philo;

typedef struct s_data
{
	pthread_t       tid;
	int             philo_num;
	int             meals_nb;
	int             dead;
	int             finished;
	t_philo         *philos;
	u_int64_t       death_time;
	u_int64_t       eat_time;
	u_int64_t       sleep_time;
	u_int64_t       start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t lock;
	pthread_mutex_t write;
} t_data;

#endif