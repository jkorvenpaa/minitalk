/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:18:22 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/08/10 19:30:34 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "libft/ft_printf.h"
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>

typedef struct s_state_server
{
	pid_t   client_pid;
	volatile sig_atomic_t	received;
	char	*str;
}   t_state_server;

typedef struct s_state_client
{
	pid_t   server_pid;
	volatile sig_atomic_t	received;
	char	*str;
}   t_state_client;

//utils
char	*update_str(char c, char *str);
char    update_char(char c, int sig, siginfo_t *info);

#endif
