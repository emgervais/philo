/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 21:43:53 by egervais          #+#    #+#             */
/*   Updated: 2023/09/20 19:57:43 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void *check_nb(t_data *data)
{
    int i;
    int finished;

    while(1)
    {
        i = 0;
        finished = 1;
        while(data->philos[i].id <= data->philo_num)
        {
            pthread_mutex_lock(&data->philos[i].lock);
            if(data->philos[i].eat_count < data->meals_nb)
                finished = 0;
            pthread_mutex_unlock(&data->philos[i++].lock);
        }
        if(finished)
        {
            pthread_mutex_lock(&data->lock);
            data->finished = 1;
            pthread_mutex_unlock(&data->lock);
            printf("Done eating\n");
            return (NULL);
        }
    }
}

void free_all(t_data *data, int err, char *mess)
{
    int i;

    i = 0;
    while(i < data->philo_num)
    {
        pthread_mutex_destroy(&data->philos[i].r_fork);
        pthread_mutex_destroy(&data->philos[i++].lock);
    }
    free(data->philos);
    free(data->forks);
    pthread_mutex_destroy(&data->lock);
    pthread_mutex_destroy(&data->write);
    free(data);
    if(err)
        exit(print_error(mess));
}

int main(int ac, char **av)
{
    t_data *data;
    int i;
    
    i = 0;
    if(ac > 6 || ac < 5 || !check_args(ac, av))
        return (print_error(ERR_AV));
    data = malloc(sizeof(t_data));
    if(!data)
        return (print_error(MALLOC_FAIL));
    if(init_data(data, av, ac) || init_p(data) || init_forks(data) || init_philo(data) || philo_start(data))
        return (1);
    if(data->meals_nb)
        check_nb(data);
    else
        while(1)
            if(is_dead(&data->philos[0]))
                break ;
    while(i < data->philo_num)
    {
        pthread_join(data->philos[i].t1, NULL);
        pthread_join(data->philos[i++].t2, NULL);
    }
    free_all(data, 0, 0);
}