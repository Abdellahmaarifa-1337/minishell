/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:48:30 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/02 08:11:41 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value && (tmp->value)[0])
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_exit_status = 0;
	return ;
}
