/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 08:45:31 by makurz            #+#    #+#             */
/*   Updated: 2023/04/23 00:54:38 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	acknowledge_signal(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
		++received;
	else
	{
		ft_putnbr_fd(received, 1);
		write(1, "\n", 1);
		exit(EXIT_SUCCESS);
	}
}

void	send_package(char *str, pid_t pid)
{
	int		bit;
	char	package;

	while (*str)
	{
		bit = 8;
		package = *str++;
		while (bit--)
		{
			if (package >> bit & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(AWAIT);
		}
	}
	bit = 8;
	while (bit--)
	{
		kill(pid, SIGUSR1);
		usleep(42);
	}
}

int	main(int argc, char *argv[])
{
	char	*message;

	if (argc != 3)
	{
		write(1, "Wrong count of args. Usage: ./client PID \"Message\"\n", 51);
		return (EXIT_FAILURE);
	}
	message = argv[2];
	write(1, "Packages acknowledged: ", 23);
	signal(SIGUSR1, acknowledge_signal);
	signal(SIGUSR2, acknowledge_signal);
	send_package(message, ft_atoi(argv[1]));
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
