#include "push_swap.h"

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_putnbr(int n)
{
    long nb;

    nb = n;
    if (nb < 0)
    {
        ft_putchar('-');
        nb = -nb;
    }
    if (nb > 9)
        ft_putnbr(nb / 10);
    ft_putchar((nb % 10) + '0');
}

int     ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

static long ft_atol(const char *s)
{
    long    res;
    int     sign;

    res = 0;
    sign = 1;
    while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
        s++;
    if (*s == '-' || *s == '+')
    {
        if (*s == '-')
            sign = -1;
        s++;
    }
    while (ft_isdigit(*s))
        res = res * 10 + (*s++ - '0');
    return (res * sign);
}