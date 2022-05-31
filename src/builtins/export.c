/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:58:30 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/31 17:22:50 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	replace_env(t_env *env, t_env *tmp, int append)
{
	char	*s;

	if (ft_strncmp(env->key, tmp->key, ft_strlen(tmp->key) + 1) == 0)
	{
		s = tmp->value;
		if (append)
		{
			tmp->value = ft_strjoin(tmp->value, env->value);
			free(env->value);
		}
		else
			tmp->value = env->value;
		free(s);
		free(env->key);
		free(env);
		return (1);
	}
	return (0);
}

void	add_back_env(t_env **env_lst, t_env *env, int append)
{
	t_env	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		if (replace_env(env, tmp, append))
			return ;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp->next = env;
}

int	add_export_env(t_env **env_lst, char *s, int append)
{
	t_env	*env;

	env = create_env(s);
	if ((env->key)[ft_strlen(env->key) - 1] == '+')
	{
		(env->key)[ft_strlen(env->key) - 1] = '\0';
		append = 1;
	}
	if (is_valid_idn(env->key))
		add_back_env(env_lst, env, append);
	else
	{
		free(env->key);
		free(env->value);
		free(env);
		return (1);
	}
	return (0);
}

int	export(t_env **env_lst, char **av)
{
	int		i;
	int		exit_status;
	int		append;

	exit_status = 0;
	if (!av)
	{
		export_print(*env_lst);
		return (exit_status);
	}
	i = 1;
	append = 0;
	while (av[i])
	{
		if (add_export_env(env_lst, av[i], append))
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
