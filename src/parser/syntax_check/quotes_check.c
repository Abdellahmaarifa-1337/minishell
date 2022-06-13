/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:03:24 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/13 19:48:12 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	print_error(int single_q, int double_q, int stx_error)
{
	if (single_q != 0)
		stx_error = '\'';
	else if (double_q != 0)
		stx_error = '"';
	printf("minishell: unclosed quote (%c)\n", stx_error);
}

int	signle_quote(char *cmd_line, int *i, int *single_q)
{
	*single_q += 1;
	*i += 1;
	while (cmd_line[*i])
	{
		if (cmd_line[*i] == '\'')
		{
			*single_q -= 1;
			*i += 1;
			return (1);
		}
		*i += 1;
	}
	return (0);
}

int	double_quote(char *cmd_line, int *i, int *double_q)
{
	*double_q += 1;
	*i += 1;
	while (cmd_line[*i])
	{
		if (cmd_line[*i] == '"')
		{
			*double_q -= 1;
			*i += 1;
			return (1);
		}
		*i += 1;
	}
	return (0);
}

int	quotes_check(char *cmd_line, int *stx_error, int *end)
{
	int	i;
	int	single_q;
	int	double_q;
	int	line_lenght;

	i = 0;
	single_q = 0;
	double_q = 0;
	line_lenght = ft_strlen(cmd_line);
	while (i < line_lenght && cmd_line[i])
	{
		if (cmd_line[i] == '\'' && !signle_quote(cmd_line, &i, &single_q))
			break ;
		else if (cmd_line[i] == '"' && !double_quote(cmd_line, &i, &double_q))
			break ;
		if (cmd_line[i] != '\'' && cmd_line[i] != '"')
			i++;
	}
	*end = i;
	if (single_q != 0 || double_q != 0)
	{
		print_error(single_q, double_q, *stx_error);
		return (0);
	}
	return (1);
}
