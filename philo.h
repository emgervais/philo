/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 21:44:02 by egervais          #+#    #+#             */
/*   Updated: 2023/07/07 23:48:02 by egervais         ###   ########.fr       */
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

typedef struct s_philo
{
    
}   t_philo;

#endif