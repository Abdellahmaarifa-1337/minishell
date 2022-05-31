/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:00:15 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 13:43:15 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

int	get_token_len(char *s)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i++;
			continue ;
		}
		size++;
		i++;
	}
	return (size);
}

char	*remove_quote(char *s)
{
	int		size;
	char	*new_str;
	int		i;
	int		j;

	size = get_token_len(s);
	new_str = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i++;
			continue ;
		}
		new_str[j] = s[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	quote_removal(t_token **tokens)
{
	t_token	*temp;
	char	*str;

	temp = *tokens;
	while (temp)
	{
		str = remove_quote(temp->value);
		free(temp->value);
		temp->value = str;
		temp = temp->next;
	}
}
