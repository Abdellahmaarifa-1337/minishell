/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:12:17 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/14 01:36:59 by amaarifa         ###   ########.fr       */
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
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		else
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			write(2, stx_error, 1);
			ft_putstr_fd("'\n",2);
		}
		free(p);
		return (0);
	}
	if (p)
		free(p);
	return (1);
}
