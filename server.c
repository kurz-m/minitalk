/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 08:45:43 by makurz            #+#    #+#             */
/*   Updated: 2023/04/23 11:49:45 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	listen_for_client(int sig, siginfo_t *info, void *old)
{
	static t_package	pack;

	(void)old;
	(void)info;
	pack.byte |= (sig == SIGUSR2);
	if (++pack.index == 8)
	{
		pack.index = 0;
		if (!pack.byte)
		{
			return ;
		}
		write(1, &pack.byte, 1);
		pack.byte = 0;
	}
	else
		pack.byte <<= 1;
}

int	main(void)
{
	struct sigaction	sig;

	write(1, "Server PID: ", 12);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sig.sa_sigaction = listen_for_client;
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig, NULL) == -1)
		return (write(2, "Error with SIGUSR1 handling.\n", 29), EXIT_FAILURE);
	if (sigaction(SIGUSR2, &sig, NULL) == -1)
		return (write(2, "Error with SIGUSR2 handling.\n", 29), EXIT_FAILURE);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
