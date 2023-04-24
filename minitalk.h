/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:17:10 by makurz            #+#    #+#             */
/*   Updated: 2023/04/24 08:51:58 by makurz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

# define AWAIT 160

typedef struct s_package
{
	char	byte;
	int		index;
}	t_package;

// functions to print out the numbers etc.
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);

#endif
