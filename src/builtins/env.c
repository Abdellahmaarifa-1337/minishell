/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:48:30 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/12 13:13:12 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env(t_env *env, char **args)
{
	t_env	*tmp;

	g_exit_status = 0;
	if (args && args[0] && args[1])
	{
		//dup2(1, 2);
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[1],2);
		ft_putstr_fd(": No such file or directory\n",2);
		//dup2(1, 1);
		g_exit_status = 1;
		return ;
	}
	tmp = env;
	while (tmp)
	{
		if (tmp->value && (tmp->value)[0])
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return ;
}
