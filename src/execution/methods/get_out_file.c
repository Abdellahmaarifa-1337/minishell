/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_out_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:20:59 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/03 11:15:00 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	open_out_file(char *name)
{
	int	fd;

	fd = open(name, O_CREAT | O_RDWR);
	if (fd == -1)
	{
		perror(NULL);
		g_exit_status = 1;
		exit(g_exit_status);
	}
	return (fd);
}

int	get_out_file(t_token *tokens)
{
	t_token	*tmp;
	int		fd;

	tmp = tokens;
	fd = -1;
	while (tmp)
	{
		if (tmp->type == OUT_TRUNC || tmp->type == APPEND)
		{
			if (fd != -1)
				close(fd);
			fd = open_out_file(tmp->value);
		}
		tmp = tmp->next;
	}
	return (fd);
}
