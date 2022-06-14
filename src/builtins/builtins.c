/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:20:45 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/14 00:59:04 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_special_cmp(char	*s1, char	*s2, size_t	n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	a = (unsigned char *)ft_strdup(s1);
	b = (unsigned char *)s2;
	i = 0;
	if (!s1 || n == 0)
		return (0);
	while (a[i])
	{
		a[i] = ft_tolower(a[i]);
		i++;
	}
	i = 0;
	while (a[i] && b[i] && a[i] == b[i] && i < n - 1)
		i++;
	i = a[i] - b[i];
	free(a);
	return (i);
}

void	run_in_child(char **args, char **env)
{
	int		pid;
	int		status;

	signal(SIGINT, handler_single_cmd);
	signal(SIGQUIT, handler_single_cmd);
	pid = fork();
	if (pid < 0)
		exit(0);
	else if (pid == 0)
	{
		execve(args[0], args, env);
		wait(NULL);
		exit(0);
	}
	while (wait(&status) != -1)
		;
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (g_exit_status < 0)
		g_exit_status = (g_exit_status * -1) + 128;
}

void	exec(char **args, t_env **env_lst, int fork_it)
{
	char	**env;

	env = NULL;
	env = env_convert(*env_lst);
	if (fork_it)
		run_in_child(args, env);
	else
	{
		execve(args[0], args, env);
		exit(1);
	}
	free_env(env);
}

int	which_builtin(char *builtin)
{
	if (!builtin)
		return (0);
	if (ft_special_cmp(builtin, "echo", 5) == 0)
		return (ECHO);
	else if (ft_strncmp(builtin, "cd", 3) == 0)
		return (CD);
	else if (ft_special_cmp(builtin, "pwd", 4) == 0)
		return (PWD);
	else if (ft_strncmp(builtin, "export", 7) == 0)
		return (EXPORT);
	else if (ft_strncmp(builtin, "unset", 6) == 0)
		return (UNSET);
	else if (ft_special_cmp(builtin, "env", 4) == 0)
		return (ENV);
	else if (ft_strncmp(builtin, "exit", 5) == 0)
		return (EXIT);
	return (-1);
}

void	execute_command(char **ar, t_env **env_lst, t_cmd_list *cmd_lst, int n)
{
	int	flag;

	flag = which_builtin(ar[0]);
	if (flag == 0)
		return ;
	if (flag == ECHO)
		echo(ar);
	else if (flag == CD)
		cd(ar, env_lst);
	else if (flag == PWD)
		pwd();
	else if (flag == EXPORT)
		ft_export(env_lst, ar);
	else if (flag == UNSET)
		unset(env_lst, ar);
	else if (flag == ENV)
		env(*env_lst, ar);
	else if (flag == EXIT)
		ft_exit(ar, cmd_lst, n);
	else
		exec(ar, env_lst, n);
}
