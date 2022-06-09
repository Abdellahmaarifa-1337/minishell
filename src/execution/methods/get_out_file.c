/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_out_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:20:59 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/09 13:21:52 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	open_out_file(char *name, int out_type)
{
	int	fd;

	if (out_type == OUT_TRUNC)
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	else
		fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0777);

	if (fd == -1)
	{
		perror((const char *)name);
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
			fd = open_out_file(tmp->value, tmp->type);
		}
		tmp = tmp->next;
	}
	return (fd);
}
