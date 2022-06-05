/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:07:51 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/05 11:09:06 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*************************************************************************/
/*********************** 🚧 UNTIL CONSTRUCTION 🚧 *************************/
/*************************************************************************/

// void	run_execution(void *arg)
// {
// 	t_cmd_data	*dt;

// 	dt = (t_cmd_data *)arg;
// 	builtins(dt);
// }

// int	hello(t_cmd_list *cmd_list)
// {
// 	pid_t	*pid;
// 	int		**fd;
// 	int		i[3];

// 	pid = (pid_t *)malloc(sizeof(pid_t) * cmd_list->n_cmd);
// 	fd = (int **)malloc(sizeof(int *) * (cmd_list->n_cmd - 1));
// 	if (!pid || !fd)
// 		perror("malloc error");
// 	i[0] = -1;
// 	while (++i[0] < cmd_list->n_cmd - 1)
// 	{
// 		fd[i[0]] = (int *)malloc(sizeof(int) * 2);
// 		if (!fd[i[0]])
// 			perror("malloc error");
// 	}
// 	while (i[0] < cmd_list->n_cmd - 1)
// 	{
// 		if (pipe(fd[i[0]]) == -1)
// 			perror("pipe error");
// 		i[0] += 1;
// 	}
// 	i[0] = -1;
// 	while (++i[0] < cmd_list->n_cmd)
// 	{
// 		pid[i[0]] = fork();
// 		if (pid[i[0]] == -1)
// 			perror("fork error");
// 		else if (pid[i[0]] == 0)
// 		{
// 			if (i != 0)
// 				dup2(fd[i[0] - 1][0], STDIN_FILENO);
// 			if (i[0] != cmd_list->n_cmd - 1)
// 				dup2(fd[i[0]][1], STDOUT_FILENO);
// 			i[1] = -1;
// 			while (++i[1] < cmd_list->n_cmd - 1)
// 			{
// 				i[2] = -1;
// 				while (++i[2] < cmd_list->n_cmd - 1)
// 					close(fd[i[1]][i[2]]);
// 			}
// 			if (strcmp(parms[i[0]][0], "/bin/echo") == 0)
// 				ft_echo((char **)grepParms);
// 			else
// 				execve(parms[i[0]][0], parms[i[0]], NULL);
// 			free(pid);
// 			i[0] = -1;
// 			while (++i[0] < cmd_list->n_cmd - 1)
// 				free(fd[i[0]]);
// 			free(fd);
// 			return ;
// 		}
// 	}
// 	i[1] = -1;
// 	while (++i[1] < PARMS_NUM - 1)
// 	{
// 		i[2] = -1;
// 		while (++i[2] < PARMS_NUM - 1)
// 			close(fd[i[1]][i[2]]);
// 	}
// 	i[0] = -1;
// 	while (++i[0] < PARMS_NUM)
// 		waitpid(pid[i[0]], NULL, 0);
// 	free(pid);
// 	i[0] = -1;
// 	while (++i[0] < cmd_list->n_cmd - 1)
// 		free(fd[i[0]]);
// 	free(fd);
// 	return ;
// }

// void	execution(t_cmd_list *cmd_list)
// {
// 	hello(cmd_list);
// 	// cmd_lstiter(cmd_list, &run_execution);
// 	return ;
// }

// void	cmd_lstiter(t_cmd_list *cmd_list, void (*run_execution)(void *))
// {
// 	t_cmd_data	*dt;
// 	t_cmd		*temp;

// 	if (!cmd_list || !cmd_list->cmd || !run_execution)
// 		return ;
// 	dt->pipe = 0;
// 	dt->n_pipe = cmd_list->n_cmd;
// 	temp = cmd_list->cmd;
// 	while (temp)
// 	{
// 		dt->cmd = temp;
// 		run_execution(dt);
// 		temp = temp->next;
// 		dt->pipe++;
// 	}
// }

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
}

void	execution(t_cmd_list *cmd_lst, t_env *env_lst)
{
	char	**args;
	int		i;
	int		n;

	exec_here_doc(cmd_lst, env_lst);
	n = 0;
	while ((cmd_lst->tokens)[n])
	{
		i = 0;
		args = get_args((cmd_lst->tokens) + n);
		resolve_path(args, cmd_lst->env);
		while (args && args[i])
		{
			printf("[ARGS] : %s\n", args[i]);
			i++;
		}
		printf("int file : %d\n", get_in_file((cmd_lst->tokens)[n]));
		printf("out file : %d\n", get_out_file((cmd_lst->tokens)[n]));
		if (args)
		{
			free_args(args);
			free(args);
		}
		n++;
	}
}
