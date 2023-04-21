/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 08:45:43 by makurz            #+#    #+#             */
/*   Updated: 2023/04/21 16:49:25 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(void)
{
	pid_t		pid;
	ssize_t		check;

	check = write(1, "Server PID: ", 12);
	if (check == -1)
		exit(EXIT_FAILURE);
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	
	return (EXIT_SUCCESS);
}
