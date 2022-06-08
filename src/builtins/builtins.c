/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:20:45 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/08 04:03:52 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	which_builtin(char *builtin)
{
	if (ft_strncmp(builtin, "echo", 5) == 0)
		return (ECHO);
	else if (ft_strncmp(builtin, "cd", 3) == 0)
		return (CD);
	else if (ft_strncmp(builtin, "pwd", 4) == 0)
		return (PWD);
	else if (ft_strncmp(builtin, "export", 7) == 0)
		return (EXPORT);
	else if (ft_strncmp(builtin, "unset", 6) == 0)
		return (UNSET);
	else if (ft_strncmp(builtin, "env", 4) == 0)
		return (ENV);
	else if (ft_strncmp(builtin, "exit", 5) == 0)
		return (EXIT);
	return (-1);
}

// void	exec(char **args, t_env **env_lst)
// {
	
// }

void	execute_command(char **args, t_env *env_lst)
{
	int	flag;

	flag = which_builtin(args[0]);
	if (flag == ECHO)
		echo(args);
	else if (flag == CD)
		cd(args, env_lst);
	else if (flag == PWD)
		pwd();
	else if (flag == EXPORT)
		ft_export(&env_lst, args);
	else if (flag == UNSET)
		unset(&env_lst, args);
	else if (flag == ENV)
		env(env_lst);
	// else if (flag == EXIT)
	// 	ft_exit(args);
	// else
	// 	exec(args, &env_lst);
}
