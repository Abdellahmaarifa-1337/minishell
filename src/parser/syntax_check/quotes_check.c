/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:03:24 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/13 17:27:35 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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

int	quotes_check(char *cmd_line, int *stx_error)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (i < (int)ft_strlen(cmd_line) && cmd_line[i])
	{
		if (cmd_line[i] == '\'' && !signle_quote(cmd_line, &i, &single_q))
			break ;
		else if (cmd_line[i] == '"' && !double_quote(cmd_line, &i, &double_q))
			break ;
		if (cmd_line[i] != '\'' && cmd_line[i] != '"')
			i++;
	}
	if (single_q != 0 || double_q != 0)
	{
		if (single_q != 0)
			*stx_error = '\'';
		else
			*stx_error = '"';
		return (0);
	}
	return (1);
}
