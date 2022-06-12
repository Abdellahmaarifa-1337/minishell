/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:07:51 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/12 07:33:13 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_free(void **arr, int size)
{
	int	i;

	i = 0;
	while (i < size && arr[i])
	{
		free(arr[i]);
		i++;
	}
}

void	ft_close(int **fd, int size, int fd1, int fd2)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (fd[i][0] != fd1 && fd[i][0] != fd2)
			close(fd[i][0]);
		if (fd[i][1] != fd1 && fd[i][1] != fd2)
			close(fd[i][1]);
		i++;
	}
	return ;
}

void	execution(t_cmd_list *cmd_lst, t_env **env_lst)
{
	t_data	*dt;
	int		number_of_commands;

	number_of_commands = get_size_of_arr((void **)(cmd_lst->tokens));
	exec_here_doc(cmd_lst, *env_lst);
	if (g_exit_status < 0)
	{
		return ;
	}
	if (number_of_commands == 1)
		exec_single_cmd(cmd_lst, env_lst);
	else
	{
		dt = (t_data *)malloc(sizeof(t_data));
		if (!dt)
			exit(0);
		dt->n_cmd = number_of_commands;
		exec_multiple_cmds(cmd_lst, env_lst, dt);
		free(dt);
	}
	return ;
}
