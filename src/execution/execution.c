/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:07:51 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/11 15:59:27 by mkabissi         ###   ########.fr       */
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

void	exec_single_cmd(t_cmd_list *cmd_lst, t_env **env_lst)
{
	char	**args;
	int		stdin_saved;
	int		stdout_saved;
	int		int_out[2];

	stdin_saved = -1;
	stdout_saved = -1;
	exec_here_doc(cmd_lst, *env_lst);
	args = get_args(cmd_lst->tokens);
	/****************************************************/
	// int	i = 0;
	// while (args && args[i])
	// {
	// 	printf("[ARGS] : %s\n", args[i]);
	// 	i++;
	// }
	/***************************************************/

	if (resolve_path(args, cmd_lst->env, 0) == 0)
		return ;
	get_in_out_file((cmd_lst->tokens)[0], int_out, 0);
	if (int_out[0] == -1 || int_out[1] == -1)
	{
		g_exit_status = 1;
		return ;
	}
	if (int_out[0] > -1)
	{
		stdin_saved = dup(STDIN_FILENO);
		dup2(int_out[0], STDIN_FILENO);
	}
	if (int_out[1] > -1)
	{
		stdout_saved = dup(STDOUT_FILENO);
		dup2(int_out[1], STDOUT_FILENO);
	}
	// if (!args)
	// 	exit(1);
	execute_command(args, env_lst, cmd_lst, 1);
	if (int_out[0] > -1)
		close(int_out[0]);
	if (int_out[1] > -1)
		close(int_out[1]);
	if (stdin_saved > -1)
		dup2(stdin_saved, STDIN_FILENO);
	if (stdout_saved > -1)
		dup2(stdout_saved, STDOUT_FILENO);
	if (args)
	{
		ft_free((void **)args, get_size_of_arr((void **)args));
		free(args);
	}
	return ;
}

void	exec_multiple_cmds(t_cmd_list *cmd_lst, t_env **env_lst)
{
	pid_t	pid;
	char	**args;
	int		**fd;
	int		int_out[2];
	int		n;
	int		i;

	exec_here_doc(cmd_lst, *env_lst);
	fd = (int **)malloc(sizeof(int *) * cmd_lst->n_cmd);
	if (!fd)
		exit(0);
	i = -1;
	while (++i < cmd_lst->n_cmd)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
			exit(0);
	}
	if (pipe(fd[0]) == -1)
		exit(1);
	n = 0;
	while ((cmd_lst->tokens)[n])
	{
		if (n != cmd_lst->n_cmd - 1)
			if (pipe(fd[n + 1]) == -1)
				exit(1);
		pid = fork();
		if (pid == 0)
		{
			args = get_args((cmd_lst->tokens) + n);
			resolve_path(args, cmd_lst->env, 1);
			get_in_out_file((cmd_lst->tokens)[n], int_out, 1);
			if (int_out[0] == -1 || int_out[1] == -1)
			{
				g_exit_status = 1;
				exit(g_exit_status);
			}
			if (int_out[0] > -1)
				dup2(int_out[0], fd[n][0]);
			if (int_out[1] > -1 && n < cmd_lst->n_cmd - 1)
				dup2(int_out[1], fd[n + 1][1]);
			
			if (n == 0)
			{
				ft_close(fd, cmd_lst->n_cmd, -1, fd[n + 1][1]);
				if (int_out[0] > -1)
					dup2(int_out[0], STDIN_FILENO);
				dup2(fd[n + 1][1], STDOUT_FILENO);
			}
			else if (n != cmd_lst->n_cmd - 1)
			{
				ft_close(fd, cmd_lst->n_cmd, fd[n][0], fd[n + 1][1]);
				dup2(fd[n][0], STDIN_FILENO);
				dup2(fd[n + 1][1], STDOUT_FILENO);
			}
			else
			{
				ft_close(fd, cmd_lst->n_cmd, fd[n][0], -1);
				dup2(fd[n][0], STDIN_FILENO);
				if (int_out[1] > -1)
					dup2(int_out[1], STDOUT_FILENO);
			}
			execute_command(args, env_lst, cmd_lst, 0);

			if (args)
			{
				ft_free((void **)args, get_size_of_arr((void **)args));
				free(args);
			}
			exit(0);
		}
		n++;
	}
	ft_close(fd, cmd_lst->n_cmd, -1, -1);
	i = -1;
	int status;
	while (++i < cmd_lst->n_cmd - 1)
		wait(NULL);
	wait(&status);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	ft_free((void **)fd, cmd_lst->n_cmd);
	free(fd);
}

void	execution(t_cmd_list *cmd_lst, t_env **env_lst)
{
	cmd_lst->n_cmd = get_size_of_arr((void **)(cmd_lst->tokens));
	if (cmd_lst->n_cmd == 1)
	{
		exec_single_cmd(cmd_lst, env_lst);	
	}else
		exec_multiple_cmds(cmd_lst, env_lst);
	return ;
}
