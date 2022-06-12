/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:55:27 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/11 16:53:48 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	size_of(t_env *env_lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env_lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*create_env_str(t_env *env_node)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(env_node->key, "=");
	res = ft_strjoin(tmp, env_node->value);
	free(tmp);
	return (res);
}

char	**env_convert(t_env *env_lst)
{
	t_env	*tmp;
	char	**env;
	int		i;

	if (!env_lst)
		return (NULL);
	i = 0;
	env = (char **)malloc(sizeof(char *) * (size_of(env_lst) + 1));
	if (!env)
		exit(1);
	tmp = env_lst;
	while (tmp)
	{
		env[i] = create_env_str(tmp);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
