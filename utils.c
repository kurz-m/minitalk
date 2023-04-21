/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:15:11 by makurz            #+#    #+#             */
/*   Updated: 2023/04/21 16:23:22 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Outputs the char 'c' to the file descriptor 'fd'.
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// Outputs the number inputted to it.
void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	nb = (unsigned int) n;
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar_fd((nb % 10) + 48, fd);
}

// Calculates the sign of the number
static int	ft_sign(int c)
{
	if (c == '-')
		return (-1);
	return (1);
}

// Converts a string to an int.
// Arbitrary amount of leading white spaces, optional plus/minus sign.
int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = ft_sign(str[i++]);
	while (str[i] > 48 && str[i] < 57)
	{
		result = result * 10 + (str[i] - '0');
		++i;
	}
	return (result * sign);
}

