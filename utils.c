#include "philo.h"

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

bool print_error(char *err)
{
    return(write(2, err, 270), 1);
}

u_int64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((u_int64_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void ft_usleep(u_int64_t time)
{
    u_int64_t start;

    start = get_time();
    while(1)
    {
        if(get_time() - start > time)
            return ;
    }
}

bool is_dead(t_philo *philo)
{
        pthread_mutex_lock(&philo->data->lock);
        if(philo->data->dead || philo->data->finished)
        {
            pthread_mutex_unlock(&philo->data->lock);
            return (1);
        }
        pthread_mutex_unlock(&philo->data->lock);
        return (0);
}
