/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:55:08 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/08/09 19:19:57 by jkorvenp         ###   ########.fr       */
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

pid_t	g_current_client;

char	*update_str(char c, char *str)
{
	char	*new_str;
	int		i;
	int		len;

	len = ft_strlen(str) + 1;
	i = 0;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

void	build_message(char c)
{
	static char	*str;

	if (!str)
	{
		str = malloc(1);
		if (!str)
		{
			g_current_client = 0;
			return ;
		}
		str[0] = '\0';
	}
	if (c == '\0')
	{
		ft_printf("%s\n", str);
		kill(g_current_client, SIGUSR1);
		g_current_client = 0;
		free(str);
		str = NULL;
		return ;
	}
	str = update_str(c, str);
	if (!str)
	{
		kill(g_current_client, SIGUSR2);
		g_current_client = 0;
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
	//	kill(g_current_client, SIGUSR1);
	}
	if (sig == SIGUSR2)
	{
		c |= 0;
	//	kill(g_current_client, SIGUSR1);
	}
	bits++;
	if (bits == 8)
	{
		build_message(c);
		bits = 0;
		c = 0;
	}
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	pid_t	sender;

	sender = info->si_pid;
	(void)context;
	if (g_current_client == 0)
	{
		g_current_client = sender;
		ft_printf("New client accepted\n");
	}
	if (g_current_client == sender)
		build_char(sig);
	else
	{
		kill(sender, SIGUSR2);
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
