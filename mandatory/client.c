/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:47:13 by jomirand          #+#    #+#             */
/*   Updated: 2023/01/05 09:46:45 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	char_deconstruct(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(400);
		bit--;
	}
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	correct_input;
	int	result;

	result = 0;
	i = 0;
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

int	main(int argc, char **argv)
{
	int		i;
	int		pid;
	char	*str;

	i = 0;
	if (check_args(argc, argv) == 1)
	{
		pid = ft_atoi(argv[1]);
		str = argv[2];
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
