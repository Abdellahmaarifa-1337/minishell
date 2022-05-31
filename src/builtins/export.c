/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:58:30 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/30 13:21:00 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

char	*get_small_env(t_env *env)
{
	char	*s;
	t_env	*tmp;

	s = env;
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, s->key, ft_strlen(tmp->key) + 1) < 0)
			s = tmp;
		tmp = tmp->next;
	}
	return (s);
}

void	export_print(t_env *env)
{
	int		size_env;
	t_env	*small_env;

	size_env = get_size_env(*env);
	small_env = get_small_env(*env);
	printf("declare -x %s=\"%s\"\n", small_env->key, small_env->value);
}

int	export(t_env **env, char **av)
{
	if (!av)
	{
		export_print(*env);
		return (0);
	}
}
