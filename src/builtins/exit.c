/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 07:12:51 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/08 22:47:35 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_isnumber(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args, t_cmd_list *cmd_lst)
{
	int	size;

	size = get_size_of_arr((void **)args);
	cmd_lst->exit = 1;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (size == 1)
		g_exit_status = 0;
	else if (size == 2 && ft_isnumber(args[1]))
		g_exit_status = ft_atoi(args[1]);
	else if (size > 2 && ft_isnumber(args[1]))
	{
		cmd_lst->exit = 0;
		g_exit_status = 1;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	}
	else if (size > 1 && ft_isnumber(args[1]) == 0)
	{
		g_exit_status = 2;
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	return ;
}
