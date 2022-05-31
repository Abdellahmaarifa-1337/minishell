/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:56:59 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 13:47:36 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

t_token_source	*init_token_source(char	*cmd_line)
{
	t_token_source	*token_source;

	token_source = (t_token_source *)malloc(sizeof(t_token_source));
	if (!token_source)
		exit(1);
	token_source->source = cmd_line;
	token_source->current_position = 0;
	token_source->current_char = (token_source->source)[0];
	token_source->size = ft_strlen(cmd_line);
	return (token_source);
}

char	goto_next_char(t_token_source *token_source)
{
	token_source->current_position++;
	token_source->current_char = (token_source->source) \
	[token_source->current_position];
	return (token_source->current_char);
}

char	get_next_char(t_token_source *token_source)
{
	if (token_source->current_position + 1 < token_source->size)
		return ((token_source->source)[token_source->current_position + 1]);
	else
		return (0);
}

char	goto_last_char(t_token_source *token_source)
{
	if (token_source->current_position > 0)
	{
		token_source->current_position--;
		token_source->current_char = (token_source->source) \
		[token_source->current_position];
		return ((token_source->source)[token_source->current_position]);
	}
	else
		return (0);
}

void	skip_space(t_token_source *token_source)
{
	long	i;

	i = token_source->current_position;
	if (i < token_source->size)
	{
		while ((token_source->source)[i] == 32
			|| ((token_source->source)[i] >= 11
			&& (token_source->source)[i] <= 13))
		{
			goto_next_char(token_source);
			i++;
		}
	}
}
