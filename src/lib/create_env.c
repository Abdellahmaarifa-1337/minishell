/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:57:37 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/14 20:47:41 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_env	*create_env(char *s)
{
	t_env	*env;
	int		i;

	if (!s)
		return (NULL);
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		exit(1);
	i = get_index_char(s, '=');
	env->key = ft_substr(s, 0, i);
	env->value = ft_substr(s, i + 1, ft_strlen(s) - 1);
	env->next = NULL;
	return (env);
}
