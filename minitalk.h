/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:18:22 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/08/11 11:50:42 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "libft/ft_printf.h"
# include <signal.h>
# include <sys/types.h>
# include <stdlib.h>

typedef struct s_state_client
{
	pid_t					server_pid;
	volatile sig_atomic_t	received;
}	t_state_client;

#endif
