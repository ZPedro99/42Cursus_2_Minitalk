/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:55:23 by jomirand          #+#    #+#             */
/*   Updated: 2023/01/05 16:18:41 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	char_construct(int signal, siginfo_t *info, void *ucontext)
{
	static int	bit;
	static char	character;

	(void)ucontext;
	if (signal == SIGUSR1)
		character = character | (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		write(1, &character, 1);
		if (character == '\0')
			kill(info->si_pid, SIGUSR1);
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
	sa.sa_sigaction = &char_construct;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	while (1)
		pause();
	return (0);
}
