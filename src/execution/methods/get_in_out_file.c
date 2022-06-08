/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_out_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:01:36 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/08 11:35:22 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	open_in_file(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		perror((const char *)name);
		g_exit_status = 1;
		exit(g_exit_status);
	}
	return (fd);
}

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

int	*get_in_out_file(t_token *tokens, int *fd)
{
	t_token	*tmp;

	tmp = tokens;
	fd[0] = -1;
	fd[1] = -1;
	while (tmp)
	{
		if (tmp->type == IN_REDERCTIONT)
		{
			if (fd[0] != -1)
				close(fd[0]);
			fd[0] = open_in_file(tmp->value);
		}
		else if (tmp->type == OUT_TRUNC || tmp->type == APPEND)
		{
			if (fd[1] != -1)
				close(fd[1]);
			fd[1] = open_out_file(tmp->value, tmp->type);
		}
		tmp = tmp->next;
	}
	return (fd);
}
