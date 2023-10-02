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

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void ft_usleep(long long time)
{
    long long start;

    start = get_time();
    while(get_time() - start < time)
        usleep(100);
}

