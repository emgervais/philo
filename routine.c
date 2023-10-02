#include "philo.h"

bool print(t_philo *philo, char *str)
{
    pthread_mutex_lock(&philo->data->lock);
    if(philo->data->dead || philo->data->finished)
        return (pthread_mutex_unlock(&philo->data->lock), 1);
    printf("%llu %d %s\n", get_time() - philo->data->start_time, philo->id, str);
    pthread_mutex_unlock(&philo->data->lock);
    return(0);
}
bool life(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    if(print(philo, FORK))
        return (pthread_mutex_unlock(philo->r_fork), 1);
    pthread_mutex_lock(philo->l_fork);
    if(print(philo, FORK))
        return (pthread_mutex_unlock(philo->l_fork), 1);
    if(print(philo, EAT))
        return (pthread_mutex_unlock(philo->r_fork), pthread_mutex_unlock(philo->l_fork), 1);
    pthread_mutex_lock(&philo->lock);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->lock);
    ft_usleep(philo->data->eat_time);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_lock(&philo->lock);
    philo->eat_count++;
    pthread_mutex_unlock(&philo->lock);
    if(print(philo, SLEEP))
        return (1);
    ft_usleep(philo->data->sleep_time);
    if(print(philo, THINK))
        return (1);
    return(0);
}

void *philo_life(void *d)
{
    t_philo *philo;

    philo = d;
    if(philo->data->philo_num == 1)
    {
        printf("%llu 1 %s\n",get_time() - philo->data->start_time, FORK);
        ft_usleep(philo->time_to_die);
        return (NULL);
    }
    if(philo->id % 2 == 0)
    {
        print(philo, THINK);
        ft_usleep(philo->data->eat_time);
    }
    while(1)
        if(life(philo))
            return (NULL);
}

int eat(t_data *data, t_philo *philo)
{
    pthread_mutex_lock(&data->lock);
    data->finished = 1;
    pthread_mutex_unlock(&data->lock);
    printf("%llums %d Done eating\n", get_time() - data->start_time, philo->id);
    return (1);
}

void *check(t_data *data)
{
    t_philo *philo;
    int i;
    long long time;
    int count;

    i = 0;
    count = 0;
    philo = data->philos;
    while(1)
    {
        if(i == data->philo_num)
        {
            count = 0;
            i = 0;
        }
        pthread_mutex_lock(&philo[i].lock);
        time = philo[i].last_meal;
        pthread_mutex_unlock(&philo[i].lock);
        if(get_time() - time > philo[i].time_to_die)
        {
            pthread_mutex_lock(&data->lock);
            data->dead = 1;
            pthread_mutex_unlock(&data->lock);
            printf("%llums %d %s\n",get_time() - data->start_time, philo[i].id, DIE);
            return (pthread_mutex_unlock(&philo[i].lock), NULL);
        }
        if(data->meals_nb != 0 && !data->finished)
        {
            pthread_mutex_lock(&philo[i].lock);
            if(philo->eat_count >= data->meals_nb)
                count++;
            pthread_mutex_unlock(&philo[i].lock);
            if(count == data->philo_num)
            {
                eat(data, &philo[i]);
                return (NULL);
            }
        }
        i++;
        ft_usleep(3);
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
