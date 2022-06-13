/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:07:00 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/13 21:05:14 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
}

void	no_cmd_err(int exit_process, char *command, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(msg, 2);
	g_exit_status = 127;
	if (exit_process)
		exit(g_exit_status);
}

char	*get_right_path(char *command, char **path, int exit_process)
{
	int		i;
	char	*cmd;
	char	*temp;

	if (command && !command[0])
	{
		no_cmd_err(exit_process, "", ": command not found");
		return (0);
	}
	if (access(command, F_OK | X_OK) == 0 && !path)
	{
		return (ft_strdup(command));
	}
	else
	{
		if (ft_strchr(command, '/'))
		{
			if (access(command, F_OK | X_OK) == 0)
				return (ft_strdup(command));
			no_cmd_err(exit_process, command, ": No such file or directory");
		}
		else
		{
			i = -1;
			while (path && path[++i])
			{
				temp = ft_strjoin(path[i], "/");
				cmd = ft_strjoin(temp, command);
				free(temp);
				if (access(cmd, F_OK | X_OK) == 0)
					return (cmd);
				else
				 	free(cmd);
			}
			if (!path)
				no_cmd_err(exit_process, command, ": No such file or directory");
			else
				no_cmd_err(exit_process, command, ": command not found");
		}

		return 0;
	}
	return (cmd);
}

int	command_not_found_case(char **args, char *tmp, int exit_process)
{
	tmp = args[0];
	g_exit_status = 127;
	args[0] = ft_strjoin("minishell: ", args[0]);
	tmp = ft_strjoin(args[0], ": command not found");
	free(args[0]);
	free(tmp);
	if (exit_process)
		exit(g_exit_status);
	else
		return (0);
	return (1);
}

void	free_args(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
	{
		free(av[i]);
		i++;
	}
	if (av)
		free(av);
}

int	resolve_path(char **args, t_env **env_lst, int exit_process)
{
	char	**path;
	char	*tmp;

	if (!args || which_builtin(args[0]) != -1)
		return (1);
	tmp = get_env(*env_lst, "PATH");
	path = ft_split(tmp, ':');
	free(tmp);
	tmp = get_right_path(args[0], path, exit_process);
	if ((!tmp || !tmp[0]))
	{
		if (path)
		{
			free_path(path);
			free(path);
		}
		if (args)
			free_args(args);
		return (0);
	}
	else
	{
		free(args[0]);
		args[0] = tmp;
	}
	if (path)
	{
		free_path(path);
		free(path);
	}
	return (1);
}
