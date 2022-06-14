/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:12:17 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/14 09:56:49 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	get_error_index(int index_error, int *stx_error, int *end, int *i)
{
	if (*i < *end || *end < 0)
	{
		*stx_error = index_error;
		*end = *i;
	}
	return (0);
}

int	check_cases(char *cmd_line, int *stx_error, int *end, int *i)
{
	int	index_error;

	if (cmd_line[*i] == '>')
	{
		if (!first_check(cmd_line, i, &index_error))
			return (get_error_index(index_error, stx_error, end, i));
	}
	else if (cmd_line[*i] == '<')
	{
		if (!second_check(cmd_line, i, &index_error))
			return (get_error_index(index_error, stx_error, end, i));
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
		free(p);
		return (0);
	}
	if (p)
		free(p);
	return (1);
}
