/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:24:37 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/11 16:37:51 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	int_handler(int signal)
{
	(void) signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = -1 * (g_exit_status + 1);
}
