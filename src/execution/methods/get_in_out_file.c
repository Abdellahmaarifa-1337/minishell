/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_out_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:01:36 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/14 00:58:13 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	open_in_file(char *name, int exit_process)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		perror((const char *)name);
		g_exit_status = 1;
		if (exit_process)
			exit(g_exit_status);
	}
	return (fd);
}

int	open_out_file(char *name, int out_type, int exit_process)
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
		if (exit_process)
			exit(g_exit_status);
	}
	return (fd);
}

void	file_loop(t_token *tmp, int *fd, int *stop, int exit_process)
{
	if (tmp->type == IN_REDERCTIONT)
	{
		if (fd[0] > -1)
			close(fd[0]);
		fd[0] = open_in_file(tmp->value, exit_process);
		if (fd[0] == -1 && exit_process == 0)
			*stop = 1;
	}
	else if (tmp->type == OUT_TRUNC || tmp->type == APPEND)
	{
		if (fd[1] > -1)
			close(fd[1]);
		fd[1] = open_out_file(tmp->value, tmp->type, exit_process);
		if (fd[1] == -1 && exit_process == 0)
			*stop = 1;
	}
}

int	*get_in_out_file(t_token *tokens, int *fd, int exit_process)
{
	t_token	*tmp;
	int		stop;

	stop = 0;
	tmp = tokens;
	fd[0] = -2;
	fd[1] = -2;
	while (tmp && !stop)
	{
		file_loop(tmp, fd, &stop, exit_process);
		tmp = tmp->next;
	}
	return (fd);
}
