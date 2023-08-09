/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 21:43:53 by egervais          #+#    #+#             */
/*   Updated: 2023/08/08 20:11:05 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((u_int64_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

bool print_error(char *err)
{
    return(write(2, err, 270), 1);
}
long atop(char *num)
{
    long number;
    
    number = 0;
    while(*num == '\t' || *num == ' ' || *num == '\r')
        num++;
    if(*num == '-')
        return (-1);
    else if(*num == '+')
        num++;
    while(*num >= '0' && *num <= '9')
    {
        number = number * 10 + *num - 48;
        num++;
    }
    if(*num != '\0')
        return (-1);
    return(number);
}
bool check_args(int ac, char **av)
{
    int i;
    long num;
    
    i = 0;
    while(++i < ac)
    {
        num = atop(av[i]);
        if(num < 1 || num > INT_MAX)
            return (0);
    }
    return (1);
}
bool init_data(t_data *data, char **av, int ac)
{
    data->philo_num = atop(av[1]);
    data->death_time = atop(av[2]);
    data->eat_time = atop(av[3]);
    data->sleep_time = atop(av[4]);
    data->tid = NULL;
    data->forks = NULL;
    data->philos = NULL;
    data->meals_nb = -1;
    data->dead = 0;
    data->finished = 0;
    if(ac == 6)
        data->meals_nb = atop(av[5]);
    if(pthread_mutex_init(&data->write, NULL) || pthread_mutex_init(&data->lock, NULL))
        return (1);
    return (0);
}
bool init_p(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->philo_num);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
    if(!data->tid || !data->forks || !data->philos)
        return (1);
    return (0);
}
bool init_philo(t_data *data)
{
    int i;

    i = 0;
    while(i <= data->philo_num)
    {
        data->philos[i].data = data;
        data->philos[i].id = i + 1;
        data->philos[i].eat_count = 0;
        data->philos[i].status = 0;
        data->philos[i].eating = 0;
        data->philos[i].time_to_die = data->death_time;
        data->philos[i].l_fork = &data->forks[(i+8)%9];
        data->philos[i].r_fork = &data->forks[i];
        pthread_mutex_init(&data->philos[i++].lock, NULL);
    }
    return (0);
}
bool init_forks(t_data *data)
{
    int i;

    i = 0;
    while(i < data->philo_num)
        if(pthread_mutex_init(&data->forks[i++], NULL))
            return (1);
    return (0);
}

void *philo_life(void *d)
{
    t_philo *philo;

    philo = d;
    //if only one philo dies after time to die
    if(philo->data->philo_num == 1)
    {
        //printf take fork
        //sleep time of death
        return (NULL);
    }
    //delay half the philo
    if(philo->id % 2 == 0)
    {
        //printthink
        //sleep
    }
    //will do those actions for ever until they detect that someone dies
    while(1)
    {
        //eat-sleep-think
        break ;
    }
    return (NULL);
}
bool philo_start(t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_time();
    while(i < data->philo_num)
    {
        data->philos[i].last_meal = data->start_time;
        if(pthread_create(&data->philos[i].t1, NULL, &philo_life,
				&data->philos[i]))
            return (1);
        i++;
    }
    return (0);
}
int main(int ac, char **av)
{
    t_data *data;
    
    if(ac > 6 || ac < 5 || !check_args(ac, av))
        return (print_error(ERR_AV));
    data = malloc(sizeof(t_data));
    if(!data)
        return (print_error(MALLOC_FAIL));
    if(init_data(data, av, ac) || init_p(data) || init_forks(data) || init_philo(data) || philo_start(data))
        return (1);
}