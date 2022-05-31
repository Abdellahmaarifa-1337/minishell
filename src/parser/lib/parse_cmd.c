/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 08:13:08 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 15:22:09 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/**
* 
* Function for parsing a single cmd in a pipe line.
* The parssing flow is in this order :
*
*		@scanner		:	scan the line and generate a tokens list
*		@expander		:	expand the ($) variables.
*		@quote_removal	:	remove the quotes and join strings.
*		@create_cmd		:	build a cmd struct from the tokens list.
*
*/

void	change_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == -1)
			s[i] = '\'';
		else if (s[i] == -2)
			s[i] = '\"';
		i++;
	}
}

void	return_quotes(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
	{
		change_str(temp->value);
		temp = temp->next;
	}
}

void	falg_token(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if ((temp->value)[0] == '\0')
		{
			if (temp->type == IN_REDERCTIONT || temp->type == OUT_TRUNC
				|| temp->type == APPEND)
				temp->type = AMBIGUOUS_REDIRECT;
			else
				temp->type = EMPTY_TOKEN;
		}
		temp = temp->next;
	}
}

t_token	*parse_cmd(t_token_source *token_source)
{
	t_token	*tokens;

	tokens = lexer(token_source);
	expander(&tokens);
	falg_token(tokens);
	quote_removal(&tokens);
	return_quotes(&tokens);
	free(token_source->source);
	free(token_source);
	token_source = NULL;
	return (tokens);
}
