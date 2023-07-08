/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 21:43:53 by egervais          #+#    #+#             */
/*   Updated: 2023/07/07 23:47:42 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool print_error(int error)
{
    if(!error)
        return(write(2, ERR_AV, 270), 1);
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
    while(*num >= '1' && *num <= '9')
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
        if(num == -1 || num > INT_MAX)
            return (0);
    }
    return (1);
}
int main(int ac, char **av)
{
    if(ac > 6 || ac < 5 || !check_args(ac, av))
        return (print_error(0));
}