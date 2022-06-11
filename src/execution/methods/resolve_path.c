/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:07:00 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/11 19:59:14 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	throw_not_found_err(char *err, char *msg, int exit_process)
{
	if (err && !msg)
		ft_putendl_fd(err, STDOUT_FILENO);
	else
		perror(msg);
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
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		else
			throw_not_found_err(NULL, command, exit_process);
	}
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
	return (0);
}

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

int	command_not_found_case(char **args, char *tmp, int exit_process)
{
	tmp = args[0];
	g_exit_status = 127;
	args[0] = ft_strjoin("minishell: ", args[0]);
	tmp = ft_strjoin(args[0], ": command not found");
	free(args[0]);
	throw_not_found_err(tmp, NULL, exit_process);
	free(tmp);
	if (exit_process)
		exit(g_exit_status);
	else
		return (0);
	return (1);
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
	if ((!tmp || !tmp[0]) && !command_not_found_case(args, tmp, exit_process))
		return (0);
	else
	{
		free(args[0]);
		args[0] = tmp;
	}
	free_path(path);
	free(path);
	return (1);
}
