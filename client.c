/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 08:45:31 by makurz            #+#    #+#             */
/*   Updated: 2023/04/22 23:35:27 by makurz           ###   ########.fr       */
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
		bit = -1;
		package = *str++;
		while (++bit < 8)
		{
			////if (package >> bit & 1)
			if (package & (1 << bit))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(AWAIT);
		}
	}
	while (bit--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
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
	write(1, "Chars acknowledged: ", 20);
	signal(SIGUSR1, acknowledge_signal);
	signal(SIGUSR2, acknowledge_signal);
	send_package(message, ft_atoi(argv[1]));
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
