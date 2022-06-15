/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:24:37 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/15 22:16:21 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	int_handler(int signal)
{
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
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler_single_cmd(int signal)
{
	g_exit_status = (signal) * -1;
	fprintf(stderr, "exit_status: %d\n", g_exit_status);
	if (signal == SIGQUIT)
		printf("^\\Quit: 3\n");
	else if (signal == SIGINT)
		printf("^C\n");
}
