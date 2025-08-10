/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:48:24 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/08/10 15:31:29 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
char    update_char(char c, int sig, siginfo_t *info)
{
	c = c << 1;
	if (sig == SIGUSR1)
	{
		c |= 1;
	//	kill(info->si_pid, SIGUSR2);
	}
	if (sig == SIGUSR2)
	{
		c |= 0;
		kill(info->si_pid, SIGUSR2);
	}
    return (c);
}