/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:13:46 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/13 18:08:53 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_node(t_env **env)
{
	if (!(*env))
		return ;
	free((*env)->key);
	free((*env)->value);
	free((*env));
}

void	init_vars(t_env **tmp, t_env **prev, int *i, t_env **env)
{
	*tmp = *env;
	*prev = NULL;
	*i = 0;
}

void	delete_node(t_env **env, int index)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	init_vars(&tmp, &prev, &i, env);
	while (tmp)
	{
		if (i == index && !prev)
		{
			prev = *env;
			*env = (*env)->next;
			free_node(&prev);
			break ;
		}
		else if (i == index)
		{
			prev->next = tmp->next;
			free_node(&tmp);
			break ;
		}
		i++;
		prev = tmp;
		tmp = tmp->next;
	}
}

void	unset_var(t_env **env, char *s)
{
	t_env	*tmp;
	int		i;

	if (!is_valid_idn(s))
	{
		g_exit_status = 1;
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
	tmp = *env;
	i = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, s, ft_strlen(tmp->key) + 1))
		{
			delete_node(env, i);
			break ;
		}
		i++;
		tmp = tmp->next;
	}
	return ;
}

void	unset(t_env **env, char **av)
{
	int	i;

	g_exit_status = 0;
	i = 1;
	while (av[i])
	{
		unset_var(env, av[i]);
		i++;
	}
	return ;
}
