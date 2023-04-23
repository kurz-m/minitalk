/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 08:45:31 by makurz            #+#    #+#             */
/*   Updated: 2023/04/23 11:48:54 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	send_package(message, ft_atoi(argv[1]));
	return (EXIT_SUCCESS);
}
