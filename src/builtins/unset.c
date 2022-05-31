/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:13:46 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/30 10:57:47 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_idn(char *s)
{
	if (ft_isalpha(s[0]) || s[0] == '_')
		return (1);
	return (0);
}

void	free_node(t_env **env)
{
	free((*env)->key);
	free((*env)->value);
	free((*env));
}

void	delete_node(t_env **env, int index)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	tmp = *env;
	prev = NULL;
	i = 0;
	while (tmp)
	{
		if (i == index && !prev)
		{
			prev = *env;
			*env = (*env)->next;
			free_node(&prev);
		}
		else if (i == index)
		{
			prev->next = tmp->next;
			free_node(&tmp);
		}
		i++;
		prev = tmp;
		tmp = tmp->next;
	}
}

int	unset_var(t_env **env, char *s)
{
	t_env	*tmp;
	int		i;

	if (!is_valid_idn(s))
		return (1);
	tmp = *env;
	i = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, s, ft_strlen(tmp->key)))
		{
			printf("going to delete : %s == %s\n", tmp->key, s);
			delete_node(env, i);
			break ;
		}
		i++;
		tmp = tmp->next;
	}
	return (0);
}

int	unset(t_env **env, char **av)
{
	int	exit_status;
	int	i;

	exit_status = 0;
	i = 1;
	while (av[i])
	{
		if (unset_var(env, av[i]))
			exit_status = 1;
		i++;
	}
	return (exit_status);
}