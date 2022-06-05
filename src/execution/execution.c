/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:07:51 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/05 18:40:31 by mkabissi         ###   ########.fr       */
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
//	t_data	dt;

// 	dt.pid = (pid_t *)malloc(sizeof(pid_t) * cmd_list->n_cmd);
// 	dt.fd = (int **)malloc(sizeof(int *) * (cmd_list->n_cmd - 1));
// 	if (!dt.pid || !dt.fd)
// 		perror("malloc error");
// 	dt.a = -1;
// 	while (++dt.a < cmd_list->n_cmd - 1)
// 	{
// 		dt.fd[dt.a] = (int *)malloc(sizeof(int) * 2);
// 		if (!dt.fd[dt.a])
// 			perror("malloc error");
// 	}
// 	while (dt.a < cmd_list->n_cmd - 1)
// 	{
// 		if (pipe(dt.fd[dt.a]) == -1)
// 			perror("pipe error");
// 		dt.a += 1;
// 	}
// 	dt.a = -1;
// 	while (++dt.a < cmd_list->n_cmd)
// 	{
// 		dt.pid[dt.a] = fork();
// 		if (dt.pid[dt.a] == -1)
// 			perror("fork error");
// 		else if (dt.pid[dt.a] == 0)
// 		{
// 			if (dt.a != 0)
// 				dup2(dt.fd[dt.a - 1][0], STDIN_FILENO);
// 			if (dt.a != cmd_list->n_cmd - 1)
// 				dup2(dt.fd[dt.a][1], STDOUT_FILENO);
// 			dt.b = -1;
// 			while (++dt.b < cmd_list->n_cmd - 1)
// 			{
// 				dt.c = -1;
// 				while (++dt.c < cmd_list->n_cmd - 1)
// 					close(dt.fd[dt.b][dt.c]);
// 			}
// 			if (strcmp(parms[dt.a][0], "/bin/echo") == 0)
// 				ft_echo((char **)grepParms);
// 			else
// 				execve(parms[dt.a][0], parms[dt.a], NULL);
// 			free(dt.pid);
// 			dt.a = -1;
// 			while (++dt.a < cmd_list->n_cmd - 1)
// 				free(dt.fd[dt.a]);
// 			free(dt.fd);
// 			return ;
// 		}
// 	}
// 	dt.b = -1;
// 	while (++dt.b < PARMS_NUM - 1)
// 	{
// 		dt.c = -1;
// 		while (++dt.c < PARMS_NUM - 1)
// 			close(dt.fd[dt.b][dt.c]);
// 	}
// 	dt.a = -1;
// 	while (++dt.a < PARMS_NUM)
// 		waitpid(dt.pid[dt.a], NULL, 0);
// 	free(dt.pid);
// 	dt.a = -1;
// 	while (++dt.a < cmd_list->n_cmd - 1)
// 		free(dt.fd[dt.a]);
// 	free(dt.fd);
// 	return ;
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

int	get_number_of_cmds(t_token **tokens)
{
	int	len;

	len = 0;
	while (tokens && tokens[len])
		len++;
	return (len);
}

void	execution(t_cmd_list *cmd_lst, t_env *env_lst)
{
	t_data	dt;
	char	**args;
	int		n;

/*********************** INIT PIDs AND PIPEs FILES ************************/
	args = NULL;
	cmd_lst->n_cmd = get_number_of_cmds(cmd_lst->tokens);
	printf("cmd: %d\n", cmd_lst->n_cmd);
	dt.pid = (pid_t *)malloc(sizeof(pid_t) * cmd_lst->n_cmd);
	dt.fd = (int **)malloc(sizeof(int *) * 2);
	if (!dt.pid || !dt.fd)
		perror("malloc error");
	dt.a = -1;
	while (++dt.a < 2)
	{
		dt.fd[dt.a] = (int *)malloc(sizeof(int) * 2);
		if (!dt.fd[dt.a])
			perror("malloc error");
	}
	while (dt.a < 2)
	{
		if (pipe(dt.fd[dt.a]) == -1)
			perror("pipe error");
		dt.a += 1;
	}
/**************************************************************************/
	exec_here_doc(cmd_lst, env_lst);
	n = 0;
	dt.a = 0;
	while ((cmd_lst->tokens)[n])
	{
		dt.pid[dt.a] = fork();
		if (dt.pid[dt.a] == -1)
			perror("fork error");
		if (dt.pid[dt.a] == 0)
		{
			/************* START PIPELINES ***************/
			if (dt.a != 0)
				dup2(dt.fd[dt.a - 1][0], STDIN_FILENO);
			if (dt.a != cmd_lst->n_cmd - 1)
				dup2(dt.fd[dt.a][1], STDOUT_FILENO);
			dt.b = -1;
			while (++dt.b < 2)
			{
				dt.c = -1;
				while (++dt.c < 2)
					close(dt.fd[dt.b][dt.c]);
			}
			/********************************************/
			dt.i = 0;
			args = get_args((cmd_lst->tokens) + n);
			resolve_path(args, cmd_lst->env);
			while (args && args[dt.i])
			{
				printf("[ARGS] : %s\n", args[dt.i]);
				dt.i++;
			}
			printf("int file : %d\n", get_in_file((cmd_lst->tokens)[n]));
			printf("out file : %d\n", get_out_file((cmd_lst->tokens)[n]));
			if (args)
			{
				free_args(args);
				free(args);
			}
			/************ FREE PIDs AND FILES ALLOC. ***********/
			free(dt.pid);
			dt.c = -1;
			while (++dt.c < 2)
				free(dt.fd[dt.c]);
			free(dt.fd);
			/***************************************************/
			exit(0) ;
		}
		waitpid(dt.pid[dt.a], NULL, 0);
		if (++dt.a == 2)
			dt.a = 0;
		n++;
	}
	/************** CLOSING PIPE/FILES *****************/
	dt.b = -1;
	while (++dt.b < 2)
	{
		dt.c = -1;
		while (++dt.c < 2)
			close(dt.fd[dt.b][dt.c]);
	}
	// dt.a = -1;
	// while (++dt.a < cmd_lst->n_cmd)
	// 	wait(NULL);
	/***************************************************/
	free(dt.pid);
	return ;
}
