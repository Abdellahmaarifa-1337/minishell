/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 22:34:36 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 13:48:02 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*add_back_token(t_token **token, t_token	*new_token)
{
	t_token		*temp;

	if (!(*token))
	{
		*token = new_token;
		new_token->next = NULL;
		return (*token);
	}
	temp = (*token);
	while (temp)
	{
		if (!temp->next)
			break ;
		temp = temp->next;
	}
	temp->next = new_token;
	return (new_token);
}

void	delete_token(t_token **token)
{
	t_token	*temp;
	t_token	*tmp;

	temp = *token;
	while (temp)
	{
		tmp = temp;
		temp = temp->next;
		free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
	free(temp);
	return ;
}

long	get_type_next_token(t_token *token)
{
	if (token->next)
		return ((token->next)->type);
	return (0);
}
