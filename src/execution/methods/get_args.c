/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 08:42:51 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/13 11:02:14 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	get_size_of_args(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**get_args(t_token **tokens)
{
	int		size;
	char	**args;
	int		i;
	t_token	*tmp;

	size = get_size_of_args(*tokens);
	if (!size)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args)
		exit(1);
	i = 0;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			args[i] = ft_strdup(tmp->value);
			i++;
		}
		tmp = tmp->next;
	}
	args[size] = NULL;
	return (args);
}
