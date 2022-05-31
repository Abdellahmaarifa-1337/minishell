/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 23:49:43 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 15:25:24 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

int	skip_chars(t_token_source *token_source, char *c)
{
	if (*c == '\'')
	{
		*c = goto_next_char(token_source);
		while (*c && *c != '\'')
			*c = goto_next_char(token_source);
		if (!*c)
			return (0);
		*c = goto_next_char(token_source);
		return (1);
	}
	if (*c == '\"')
	{
		*c = goto_next_char(token_source);
		while (*c && *c != '\"')
			*c = goto_next_char(token_source);
		if (!*c)
			return (0);
		*c = goto_next_char(token_source);
		return (1);
	}
	*c = goto_next_char(token_source);
	return (1);
}

t_token	*collect_string(t_token_source *token_source, int type)
{
	int		start;
	char	c;
	t_token	*new_token;

	start = token_source->current_position;
	c = token_source->current_char;
	while (c && c != 32 && c != '<' && c != '>')
	{
		if (skip_chars(token_source, &c))
			continue ;
		else
			break ;
	}
	new_token = create_token(ft_substr(token_source->source, start,
				token_source->current_position - start), type);
	return (new_token);
}

int	get_in_tokens(t_token **token, t_token_source *token_source)
{
	if (!goto_next_char(token_source))
		return (0);
	if (token_source->current_char && token_source->current_char == '<')
	{
		if (!goto_next_char(token_source))
			return (0);
		skip_space(token_source);
		add_back_token(token, collect_string(token_source, HERE_DOC));
		return (1);
	}
	else
	{
		skip_space(token_source);
		add_back_token(token, collect_string(token_source, IN_REDERCTIONT));
		return (1);
	}
}

int	get_out_tokens(t_token **token, t_token_source *token_source)
{
	if (!goto_next_char(token_source))
		return (0);
	if (token_source->current_char && token_source->current_char == '>')
	{
		if (!goto_next_char(token_source))
			return (0);
		skip_space(token_source);
		add_back_token(token, collect_string(token_source, APPEND));
		return (1);
	}
	else
	{
		skip_space(token_source);
		add_back_token(token, collect_string(token_source, OUT_TRUNC));
		return (1);
	}
}

t_token	*lexer(t_token_source *token_source)
{
	t_token	*token;

	token = NULL;
	while (token_source->current_char)
	{
		skip_space(token_source);
		if (token_source->current_char && token_source->current_char == '<')
		{
			if (get_in_tokens(&token, token_source))
				continue ;
			else
				break ;
		}
		else if (token_source->current_char
			&& token_source->current_char == '>')
		{
			if (get_out_tokens(&token, token_source))
				continue ;
			else
				break ;
		}
		skip_space(token_source);
		add_back_token(&token, collect_string(token_source, WORD));
	}
	return (token);
}
