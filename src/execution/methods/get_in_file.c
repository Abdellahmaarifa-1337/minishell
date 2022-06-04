/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:01:36 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/03 11:15:17 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	open_in_file(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		perror(NULL);
		g_exit_status = 1;
		exit(g_exit_status);
	}
	return (fd);
}

int	get_in_file(t_token *tokens)
{
	t_token	*tmp;
	int		fd;

	tmp = tokens;
	fd = -1;
	while (tmp)
	{
		if (tmp->type == IN_REDERCTIONT)
		{
			if (fd != -1)
				close(fd);
			fd = open_in_file(tmp->value);
		}
		tmp = tmp->next;
	}
	return (fd);
}