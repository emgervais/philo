/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 21:43:53 by egervais          #+#    #+#             */
/*   Updated: 2023/09/30 21:18:25 by egervais         ###   ########.fr       */
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

void free_all(t_data *data, int err, char *mess)
{
    int i;

    i = 0;
    while(i < data->philo_num)
    {
        pthread_mutex_destroy(data->philos[i].r_fork);
        pthread_mutex_destroy(&data->philos[i++].lock);
    }
    free(data->philos);
    free(data->forks);
    pthread_mutex_destroy(&data->lock);
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
    check(data);
    while(i < data->philo_num)
        pthread_join(data->philos[i++].t1, NULL);
    free_all(data, 0, 0);
}