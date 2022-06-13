/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:24:37 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/13 13:16:20 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	int_handler(int signal)
{

	//printf("handler 1 worinng with %d\n", g_exit_status);
	if (signal == SIGINT)
	{
		g_exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		g_exit_status = 0;
		// printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void handler_single_cmd(int signal)
{
	g_exit_status = (signal) * -1;
	printf("\n");
}