/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:55:08 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/08/06 18:41:11 by jkorvenp         ###   ########.fr       */
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

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("Server PID = %d\n", pid);
	//loop_for_signal_listening();
	//react_to_signal();
	
}