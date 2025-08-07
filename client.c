/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:54:38 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/08/07 16:38:26 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Write a program (main) in which the client takes two parameters/arguments

	The PID of the server to which it wants to send the message

	A message

Encrypt the message (I did the encryption via bits)

Send the message to the server (via its PID)

Create a stop condition so that the server knows when it has finished receiving the message

*/


//for bit on = 1
	//kill(pid, SIGUSR1);
//for bit off = 0
	//kill(pid, SIGUSR2);
#include "minitalk.h"

void	send_bits(char	c, int pid)
{
	int	j;
	int	bit;

	j = 7;
	while (j >= 0)
	{
		bit = (c >> j) &1;
		if (bit == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		j--;
	}
}

void	encrypt_message(char *message, int pid)
{
	char	c;
	int	i;

	i = 0;
	while(message[i])
	{
		c = message[i];
		send_bits(c, pid);
		i++;
	}
	c = '\0';
	send_bits(c, pid);
}

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf("message completed\n");
		exit(EXIT_SUCCESS);
	}
	if (sig == SIGUSR2)
	{
		ft_printf("message ignored, other client in process\n");
		exit(EXIT_FAILURE);
	}
}
int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf("invalid arguments\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 0)
	{
		ft_printf("invalid pid\n");
		return(1);
	}
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	encrypt_message(argv[2], pid);
	while(1)
		pause();
	return (0);
}