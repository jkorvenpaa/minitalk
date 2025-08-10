/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:55:08 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/08/10 20:11:45 by jkorvenp         ###   ########.fr       */
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

//pid_t	g_current_client;

t_state_server	g_server;


int	server_timeout()
{
	int	time;
	
	time = 0;
	while (g_server.received == 1)
	{
		usleep(100);
		time++;
		if (time > 1000)
		{
			ft_printf("timeout\n");
			g_server.client_pid = 0;
			return (1);
		}
	}
	return (0);
}
void	build_message(char c)
{
	static char	*str;

	if (!str)
	{
		str = malloc(1);
		if (!str)
		{
			g_server.client_pid = 0;
			return ;
		}
		str[0] = '\0';
	}
	if (c == '\0')
	{
		ft_printf("%s\n", str);
		kill(g_server.client_pid, SIGUSR1);
		g_server.client_pid = 0;
		free(str);
		str = NULL;
		return ;
	}
	str = update_str(c, str);
	if (!str)
	{
		kill(g_server.client_pid, SIGUSR2);
		g_server.client_pid = 0;
		free(str);
		str = NULL;
	}
}

void	build_char(int sig)
{
	static char	c = 0;
	static int	bits;

	c = c << 1;
	if (sig == SIGUSR1)
	{
		c |= 1;
		kill(g_server.client_pid, SIGUSR2);
	}
	if (sig == SIGUSR2)
	{
		c |= 0;
		kill(g_server.client_pid, SIGUSR2);
	}
	bits++;
	if (bits == 8)
	{
		build_message(c);
		bits = 0;
		c = 0;
	}
	g_server.received = 0;
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_server.client_pid  == 0)
	{
		g_server.client_pid = info->si_pid;;
		ft_printf("New client accepted\n");
	}
	if (g_server.client_pid  == info->si_pid)
	{
		g_server.received = 1;
		//if(server_timeout() == 1)
		// 	return;
		build_char(sig);
		
		//free (g_server.str);
	}
	else
	{
		ft_printf("New client denied\n");
		return ;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;
	

	pid = getpid();
	if (pid < 0)
		return (1);
	ft_printf("Server PID = %d\n", pid);
	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGUSR1);
	sigaddset(&action.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
