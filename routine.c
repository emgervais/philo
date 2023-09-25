#include "philo.h"

bool philo_start(t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_time();
    while(i < data->philo_num)
    {
        data->philos[i].last_meal = data->start_time;
        if(pthread_create(&data->philos[i].t2, NULL, &check, &data->philos[i]))
            return (1);
        if(pthread_create(&data->philos[i].t1, NULL, &philo_life,
				&data->philos[i]))
            return (1);
        i++;
    }
    return (0);
}

void *philo_life(void *d)
{
    t_philo *philo;

    philo = d;
    if(philo->data->philo_num == 1)
    {
        printf("%llu philo #1 %s\n",get_time() - philo->data->start_time, FORK);
        ft_usleep(philo->time_to_die);
        return (NULL);
    }
    if(philo->id % 2 == 0)
    {
        printf("%llu philo #%d %s\n", get_time() - philo->data->start_time, philo->id, THINK);
        ft_usleep(philo->data->eat_time / 2);
    }
    while(1)
        if(cprintf(philo))
            return (NULL);
    return (NULL);
}

void *check(void *d)
{
    t_philo *philo;

    philo = d;
    while(1)
    {
        if(is_dead(philo))
            return (NULL);
        pthread_mutex_lock(&philo->lock);
        if(get_time() - philo->last_meal >= philo->time_to_die)
        {
            pthread_mutex_lock(&philo->data->lock);
            philo->data->dead = 1;
            printf("%llu philo #1 %s\n",get_time() - philo->data->start_time, DIE);
            pthread_mutex_unlock(&philo->data->lock);
            pthread_mutex_unlock(&philo->lock);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->lock);
    }
    return (NULL);
}

bool cprintf(t_philo *philo)
{
        if(is_dead(philo))
            return (1);
        pthread_mutex_lock(philo->l_fork);
        printf("%llu philo #%d %s\n", get_time() - philo->data->start_time, philo->id, FORK);
        pthread_mutex_lock(philo->r_fork);
        printf("%llu philo #%d %s\n", get_time() - philo->data->start_time, philo->id, FORK);
        printf("%llu philo #%d %s\n", get_time() - philo->data->start_time, philo->id, EAT);
        pthread_mutex_lock(&philo->lock);
        philo->last_meal = get_time();
        philo->eat_count++;
        pthread_mutex_unlock(&philo->lock);
        ft_usleep(philo->data->eat_time);
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        if(is_dead(philo))
            return (1);
        printf("%llu philo #%d %s\n", get_time() - philo->data->start_time, philo->id, SLEEP);
        ft_usleep(philo->data->sleep_time);
        if(is_dead(philo))
            return (1);
        printf("%llu philo #%d %s\n", get_time() - philo->data->start_time, philo->id, THINK);
    return(0);
}

