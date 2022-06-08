/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:07:00 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/08 11:47:23 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	throw_not_found_err(char *err, int exit_bool)
{
	if (err)
		printf("%s\n", err);
	else
		perror(err);
	g_exit_status = 127;
	if (exit_bool)
		exit(g_exit_status);
}

char	*get_right_path(char *command, char **path)
{
	int		i;
	char	*cmd;
	char	*temp;

	i = 0;
	if (command && !command[0])
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		else
			throw_not_found_err(NULL, 1);
	}
	while (path && path[i])
	{
		temp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(temp, command);
		free(temp);
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		else
			free(cmd);
		i++;
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

void	resolve_path(char **args, t_env **env_lst)
{
	char	**path;
	char	*tmp;

	if (!args || which_builtin(args[0]) != -1)
		return ;
	tmp = get_env(*env_lst, "PATH");
	path = ft_split(tmp, ':');
	free(tmp);
	tmp = get_right_path(args[0], path);
	if (!tmp || !tmp[0])
	{
		tmp = args[0];
		args[0] = ft_strjoin("minishell: ", args[0]);
		free(args[0]);
		tmp = ft_strjoin(args[0], ": command not found");
		throw_not_found_err(tmp, 0);
		free(tmp);
		exit(g_exit_status);
	}
	else
	{
		free(args[0]);
		args[0] = tmp;
	}
	free_path(path);
	free(path);
}
