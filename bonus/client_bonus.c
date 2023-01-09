/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:55:01 by jomirand          #+#    #+#             */
/*   Updated: 2023/01/05 16:24:47 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	char_deconstruct(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (c >> bit & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(200);
		bit--;
	}
}

int	check_args(int argc, char **argv)
{
	int	correct_input;

	correct_input = 0;
	(void)argv;
	if (argc != 3)
	{
		ft_printf("Invalid number of arguments\n");
		return (0);
	}
	else
		correct_input = 1;
	return (correct_input);
}

void	message_received(int signal, siginfo_t *info, void *ucontext)
{
	(void)signal;
	(void)info;
	(void)ucontext;
	ft_printf("Message received!\n");
}

int	main(int argc, char **argv)
{
	int					i;
	int					pid;
	char				*str;
	struct sigaction	sa;

	i = 0;
	if (check_args(argc, argv) == 1)
	{
		sa.sa_sigaction = &message_received;
		sa.sa_flags = SA_SIGINFO;
		pid = ft_atoi(argv[1]);
		str = argv[2];
		if (sigaction(SIGUSR1, &sa, NULL) == -1)
			ft_printf("%s\n", "Failed to send signal");
		while (*(str + i))
		{
			char_deconstruct(pid, *(str + i));
			i++;
		}
		char_deconstruct(pid, '\n');
		char_deconstruct(pid, '\0');
	}
	return (0);
}
