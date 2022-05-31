/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:48:30 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/30 11:57:18 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value && (tmp->value)[0])
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
