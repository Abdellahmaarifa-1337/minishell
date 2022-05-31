/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:20:45 by mkabissi          #+#    #+#             */
/*   Updated: 2022/05/31 17:31:27 by mkabissi         ###   ########.fr       */
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

// void	builtins(t_cmd_data *dt)
// {
// 	int	flag;

// 	flag = which_builtin(dt->cmd->cmds[0]);
// 	if (flag == ECHO)
// 		ft_echo(dt);
// 	else if (flag == CD)
// 		ft_chdir(dt);
// 	else if (flag == PWD)
// 		ft_pwd();
// 	else if (flag == EXPORT)
// 		ft_export(dt);
// 	else if (flag == UNSET)
// 		ft_unset(dt);
// 	else if (flag == ENV)
// 		ft_env(dt);
// 	else if (flag == EXIT)
// 		ft_exit(dt);
// 	else
// 		exec();	
// }
