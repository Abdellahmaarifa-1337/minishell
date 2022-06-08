/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 07:12:51 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/08 07:27:33 by mkabissi         ###   ########.fr       */
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

void	ft_exit(char **args, int *exit)
{
	int	size;

	size = get_size_of_arr(args);
	*exit = 1;
	ft_putendl_fd("exit", stderr);
	if (size == 1)
		g_exit_status = 0;
	else if (size == 2 && ft_isnumber(args[1]))
		g_exit_status = ft_atoi(args[1]);
	else if (size > 2 && ft_isnumber(args[1]))
	{
		*exit = 0;
		g_exit_status = 1;
		ft_putendl_fd("minishell: exit: too many arguments", stderr);
	}
	else if (size > 1 && ft_isnumber(args[1]) == 0)
	{
		g_exit_status = 2;
		ft_putstr_fd("minishell: exit: ", stderr);
		ft_putstr_fd(args[1], stderr);
		ft_putendl_fd(": numeric argument required", stderr);
	}
	return ;
}
