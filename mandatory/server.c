/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:50:23 by jomirand          #+#    #+#             */
/*   Updated: 2023/01/06 09:40:38 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	char_construct(int signal)
{
	static int	bit;
	static char	character;

	if (signal == SIGUSR1)
		character |= (1 << (7 - bit));
	if (signal == SIGUSR2)
		character |= (0 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		write(1, &character, 1);
		bit = 0;
		character = 0;
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Invalid number of arguments\n");
		return (0);
	}
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &char_construct;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	while (1)
		pause();
	return (0);
}
