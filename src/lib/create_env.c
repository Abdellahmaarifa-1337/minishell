/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:57:37 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/30 14:58:06 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	get_index_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

t_env	*create_env(char *s)
{
	t_env	*env;
	int		i;

	if (!s)
		return (NULL);
	env = (t_env *)malloc(sizeof(t_env));
	i = get_index_char(s, '=');
	env->key = ft_substr(s, 0, i);
	env->value = ft_substr(s, i + 1, ft_strlen(s) - 1);
	env->next = NULL;
	return (env);
}
