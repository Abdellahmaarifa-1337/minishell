/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:12:37 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/02 07:22:41 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	add_env_back(t_env *env, t_env *new_env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp->next = new_env;
}

t_env	*set_env(char **env)
{
	int		i;
	t_env	*env_lst;
	t_env	*tmp;

	env_lst = create_env(env[0]);
	if (!env_lst)
		return (NULL);
	tmp = env_lst;
	i = 1;
	while (env[i])
	{
		add_env_back(tmp, create_env(env[i]));
		tmp = tmp->next;
		i++;
	}
	return (env_lst);
}
