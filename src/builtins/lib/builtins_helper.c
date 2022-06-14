/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:11:26 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/14 03:18:33 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	get_size_of_arr(void **tokens)
{
	int	len;

	len = 0;
	while (tokens && tokens[len])
		len++;
	return (len);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		free(env[i]);
		i++;
	}
	if (env)
		free(env);
}

char	*ft_getenv(char *name, t_env **env_lst)
{
	t_env	*temp;

	if (!*env_lst || !name)
		return (NULL);
	temp = *env_lst;
	while (temp)
	{
		if (ft_strcmp(name, temp->key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
