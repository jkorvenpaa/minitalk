/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:55:08 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/08/11 11:41:16 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

pid_t	g_client_pid;

char	*update_str(char c, char *str)
{
	char	*new_str;
	int		i;
	int		len;

	len = ft_strlen(str) + 1;
	i = 0;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
	{
		free(str);
		g_client_pid = 0;
		return (NULL);
	}
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
			g_client_pid = 0;
			str = NULL;
			return ;
		}
		str[0] = '\0';
	}
	if (c == '\0')
	{
		ft_printf("%s\n", str);
		kill(g_client_pid, SIGUSR1);
		g_client_pid = 0;
		free(str);
		str = NULL;
		return ;
	}
	str = update_str(c, str);
}

void	build_char(int sig)
{
	static char	c = 0;
	static int	bits;

	c = c << 1;
	if (sig == SIGUSR1)
	{
		c |= 1;
		kill(g_client_pid, SIGUSR2);
	}
	if (sig == SIGUSR2)
	{
		c |= 0;
		kill(g_client_pid, SIGUSR2);
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
	(void) context;
	if (g_client_pid == 0)
	{
		g_client_pid = info->si_pid;
		ft_printf("New client accepted\n");
	}
	build_char(sig);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;

	pid = getpid();
	if (pid <= 0)
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
