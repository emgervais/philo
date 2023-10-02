#include "philo.h"

bool init_data(t_data *data, char **av, int ac)
{
    data->philo_num = atop(av[1]);
    data->death_time = atop(av[2]);
    data->eat_time = atop(av[3]);
    data->sleep_time = atop(av[4]);
    data->meals_nb = 0;
    data->forks = NULL;
    data->philos = NULL;
    data->dead = 0;
    data->finished = 0;
    if(ac == 6)
        data->meals_nb = atop(av[5]);
    if(pthread_mutex_init(&data->lock, NULL))
        return (1);
    return (0);
}

bool init_p(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
    if(!data->forks || !data->philos)
        return (1);
    return (0);
}

bool init_philo(t_data *data)
{
    int i;

    i = 0;
    while(i < data->philo_num)
    {
        data->philos[i].data = data;
        data->philos[i].id = i + 1;
        data->philos[i].eat_count = 0;
        data->philos[i].status = 0;
        data->philos[i].eating = 0;
        data->philos[i].time_to_die = data->death_time;
        data->philos[i].l_fork = &data->forks[i + 1];
        if(i + 1 == data->philo_num)
            data->philos[i].l_fork = &data->forks[0];
        data->philos[i].r_fork = &data->forks[i];
        if(pthread_mutex_init(&data->philos[i++].lock, NULL))
            return (1);
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

