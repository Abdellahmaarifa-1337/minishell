/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:46:50 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/30 14:48:08 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	get_size_env(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_env	*get_small_env(t_env *env_lst)
{
	t_env	*s;
	t_env	*tmp;

	s = env_lst;
	tmp = env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, s->key, ft_strlen(tmp->key) + 1) < 0)
			s = tmp;
		tmp = tmp->next;
	}
	return (s);
}

t_env	*get_bigger_env(t_env *env_lst)
{
	t_env	*s;
	t_env	*tmp;

	s = env_lst;
	tmp = env_lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, s->key, ft_strlen(tmp->key) + 1) > 0)
			s = tmp;
		tmp = tmp->next;
	}
	return (s);
}

t_env	*get_next_env(t_env *env_lst, t_env *env)
{
	t_env	*s;
	t_env	*tmp;

	s = get_bigger_env(env_lst);
	tmp = env_lst;
	while (tmp)
	{
		if ((ft_strncmp(tmp->key, env->key, ft_strlen(tmp->key) + 1) > 0)
			&& (ft_strncmp(tmp->key, s->key, ft_strlen(tmp->key) + 1) < 0))
			s = tmp;
		tmp = tmp->next;
	}
	return (s);
}

void	export_print(t_env *env)
{
	int		size_env;
	t_env	*small_env;

	if (!env)
		return ;
	size_env = get_size_env(env);
	small_env = get_small_env(env);
	printf("declare -x %s=\"%s\"\n", small_env->key, small_env->value);
	size_env--;
	while (size_env > 0)
	{
		small_env = get_next_env(env, small_env);
		printf("declare -x %s=\"%s\"\n", small_env->key, small_env->value);
		size_env--;
	}
}
