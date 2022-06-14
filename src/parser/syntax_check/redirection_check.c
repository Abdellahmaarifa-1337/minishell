/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:12:17 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/14 00:31:22 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_cases(char *cmd_line, int *stx_error, int *end, int *i)
{
	if (cmd_line[*i] == '>')
	{
		if (!first_check(cmd_line, i, stx_error))
		{
			if (*i < *end || *end < 0)
				*end = *i;
			return (0);
		}
	}
	else if (cmd_line[*i] == '<')
	{
		if (!second_check(cmd_line, i, stx_error))
		{
			if (*i < *end || *end < 0)
				*end = *i;
			return (0);
		}
	}
	return (1);
}

int	redirection_check(char *cmd_line, int *stx_error, int *end)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (!check_cases(cmd_line, stx_error, end, &i))
			return (0);
		i++;
	}
	return (1);
}

int	redirect_check(char *cmd_line, int *stx_error, int *end)
{
	char	*p;

	p = skip_quote(cmd_line);
	if (p && !redirection_check(p, stx_error, end))
	{
		if (*stx_error == '\0' || *stx_error == '\n')
			printf("minishell: syntax error near unexpected token `newline'\n");
		else
			printf("minishell: syntax error near unexpected token `%c'\n",
				*stx_error);
		free(p);
		return (0);
	}
	if (p)
		free(p);
	return (1);
}
