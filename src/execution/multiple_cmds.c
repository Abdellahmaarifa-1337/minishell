/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:01:30 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/11 21:33:41 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_dup(int *int_out, int **fd, int size, int n)
{
	if (n == 0)
	{
		ft_close(fd, size, -1, fd[n + 1][1]);
		if (int_out[0] > -1)
			dup2(int_out[0], STDIN_FILENO);
		dup2(fd[n + 1][1], STDOUT_FILENO);
	}
	else if (n != size - 1)
	{
		ft_close(fd, size, fd[n][0], fd[n + 1][1]);
		dup2(fd[n][0], STDIN_FILENO);
		dup2(fd[n + 1][1], STDOUT_FILENO);
	}
	else
	{
		ft_close(fd, size, fd[n][0], -1);
		dup2(fd[n][0], STDIN_FILENO);
		if (int_out[1] > -1)
			dup2(int_out[1], STDOUT_FILENO);
	}
}

void	exec_current_command(t_data *dt, char	**args, int *int_out,
			int **fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		args = get_args((dt->cmd_lst->tokens) + dt->n);
		resolve_path(args, dt->cmd_lst->env, 1);
		get_in_out_file((dt->cmd_lst->tokens)[dt->n], int_out, 1);
		if (int_out[0] == -1 || int_out[1] == -1)
		{
			g_exit_status = 1;
			exit(g_exit_status);
		}
		if (int_out[0] > -1)
			dup2(int_out[0], fd[dt->n][0]);
		if (int_out[1] > -1 && dt->n < dt->n_cmd - 1)
			dup2(int_out[1], fd[dt->n + 1][1]);
		ft_dup(int_out, fd, dt->n_cmd, dt->n);
		execute_command(args, dt->env_lst, dt->cmd_lst, 0);
		if (args)
		{
			ft_free((void **)args, get_size_of_arr((void **)args));
			free(args);
		}
		exit(0);
	}
}

void	exec_multiple_cmds(t_cmd_list *cmd_lst, t_env **env_lst)
{
	t_data	dt;
	char	**args;
	int		**fd;
	int		int_out[2];
	int		n;

	fd = (int **)malloc(sizeof(int *) * dt.n_cmd);
	if (!fd)
		exit(0);
	n = -1;
	while (++n < dt.n_cmd)
	{
		fd[n] = (int *)malloc(sizeof(int) * 2);
		if (!fd[n])
			exit(0);
	}
	if (pipe(fd[0]) == -1)
		exit(1);
	n = 0;
	while ((cmd_lst->tokens)[n])
	{
		if (n != dt.n_cmd - 1)
			if (pipe(fd[n + 1]) == -1)
				exit(1);
		exec_current_command();
		n++;
	}
	ft_close(fd, dt.n_cmd, -1, -1);
	n = -1;
	while (++n < dt.n_cmd - 1)
		wait(NULL);
	wait(&(cmd_lst->status));
	if (WIFEXITED(cmd_lst->status))
		g_exit_status = WEXITSTATUS(cmd_lst->status);
	ft_free((void **)fd, dt.n_cmd);
	free(fd);
}
