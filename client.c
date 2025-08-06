/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:54:38 by jkorvenp          #+#    #+#             */
/*   Updated: 2025/08/06 19:16:51 by jkorvenp         ###   ########.fr       */
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

#include "minitalk.h"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("invalid arguments\n");
		return (1);
	}
	else
		ft_printf("message = %s\n", argv[2]);
	//parse_pid(&argv[1]);
	//parse_message_to_bits(&argv[2]);
	//send_to_server();
	//stop();
}