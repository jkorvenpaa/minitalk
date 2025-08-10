/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:54:38 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/08/10 20:02:29 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
client takes two parameters/arguments, The PID of the server and message.
Encrypts and sends the message by bits
\0 char as a stop condition for server to know when the message is finnished

for bit on = 1, or success-signal
	kill(pid, SIGUSR1);
for bit off = 0, or fail signal
	kill(pid, SIGUSR2);
*/

#include "minitalk.h"

//volatile sig_atomic_t	g_note;

t_state_client	g_client;

void	client_timeout(void)
{
	int	time;
	
	time = 0;
	while (g_client.received == 0)
	{
		usleep(100);
		time++;
		if (time > 1000)
		{
			time = 0;
			ft_printf("timeout\n");
			exit(EXIT_FAILURE);
		}
	}
}

void	send_bits(char c)
{
	int	j;
	int	bit;
	

	j = 7;
	while (j >= 0)
	{
		bit = (c >> j) & 1;
		if (bit == 1)
			kill(g_client.server_pid, SIGUSR1);
		else
			kill(g_client.server_pid, SIGUSR2);
		client_timeout();
		g_client.received = 0;
		j--;
	}
}

void	encrypt_message(char *message)
{
	char	c;
	int		i;

	i = 0;
	while (message[i])
	{
		c = message[i];
		send_bits(c);
		i++;
	}
	c = '\0';
	send_bits(c);
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_client. server_pid != info->si_pid)
		exit(EXIT_FAILURE);
	if (sig == SIGUSR1)
	{
		ft_printf("message completed\n");
		exit(EXIT_SUCCESS);
	}
	if (sig == SIGUSR2)
		g_client.received = 1;   
}

int	main(int argc, char **argv)
{
	struct sigaction	action;
	
	if (argc != 3)
	{
		ft_printf("invalid arguments\n");
		return (1);
	}
	g_client.server_pid = ft_atoi(argv[1]);
	if (g_client.server_pid < 0)
	{
		ft_printf("invalid pid\n");
		return (1);
	}
	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGUSR1);
	sigaddset(&action.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	encrypt_message(argv[2]);
	while (1)
		pause();
	return (0);
}
