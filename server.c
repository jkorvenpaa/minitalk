/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:55:08 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/08/07 16:54:54 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

Display its PID

Create an endless loop so that the server can receive signals at any time

Receive signals

Decrypt signals

For each signal received (SIGUSR1 & SIGUSR2) it should take a certain action
*/

#include "minitalk.h"

pid_t	current_client;

void	display_message(int sig)
{
	static char	c = 0;
	static int bits;

	c = c << 1;
	if (sig == SIGUSR1)
		c |= 1;
	if (sig == SIGUSR2)
		c |= 0;
	
	bits++;
	if (bits == 8)
	{
		ft_printf("%c", c);
		bits = 0;
		if (c == '\0')
		{
			ft_printf("\n");
			kill(current_client, SIGUSR1);
			current_client = 0;
		}
		c = 0;
	}
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	pid_t sender = info->si_pid;
	(void)context;
	if(current_client == 0)
	{
		current_client = sender;
		ft_printf("New client accepted\n");
	}
	if (current_client == sender)
		display_message(sig);
	else
	{
		kill(sender, SIGUSR2);
		ft_printf("New client denied\n");
		return;
	}	
}

int	main(void)
{
	pid_t	pid;
	struct sigaction action;

	pid = getpid();
	if (pid < 0)
		return(1);
	ft_printf("Server PID = %d\n", pid);
	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigaddset(&action.sa_mask, SIGUSR1);
	sigaddset(&action.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while(1)
		pause();
	return(0);
}

/*		printf("message-timeout, client disconnected\n");
		kill(current_client, SIGUSR2);
		current_client = 0;*/