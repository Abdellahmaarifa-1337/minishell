/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_check_helpers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:57:55 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/13 23:58:46 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	append_mode(char *cmd_line, int *i, int *stx_error)
{
	*i += (skip_spaces(cmd_line, *i) + 1);
	if (cmd_line[*i] == '>' || cmd_line[*i] == '<' || end_of_cmd(cmd_line[*i]))
	{
		*stx_error = cmd_line[*i];
		return (0);
	}
	if (cmd_line[*i] == ' ')
		*i += skip_spaces(cmd_line, *i);
	if (cmd_line[*i] == '>' || cmd_line[*i] == '<' || end_of_cmd(cmd_line[*i]))
	{
		*stx_error = cmd_line[*i];
		return (0);
	}
	return (1);
}

int	first_check(char *cmd_line, int *i, int *stx_error)
{
	int	inc;

	if (*i != 0 && ft_isdigit(cmd_line[*i - 1]) && (cmd_line[*i - 2] == ' '
			|| end_of_cmd(cmd_line[*i])))
	{
		*stx_error = cmd_line[*i - 1];
		return (0);
	}
	inc = *i;
	if (cmd_line[*i + 1] == '>' && !append_mode(cmd_line, i, stx_error))
		return (0);
	else
	{
		if (cmd_line[*i] == ' ' || inc == *i)
			*i += skip_spaces(cmd_line, *i);
		if (cmd_line[*i] == '>' || cmd_line[*i] == '<'
			|| end_of_cmd(cmd_line[*i]))
		{
			*stx_error = cmd_line[*i];
			return (0);
		}
	}
	return (1);
}

int	heredoc_mode(char *cmd_line, int *i, int *stx_error)
{
	*i += (skip_spaces(cmd_line, *i) + 1);
	if (cmd_line[*i] == '>' || cmd_line[*i] == '<' || end_of_cmd(cmd_line[*i]))
	{
		*stx_error = cmd_line[*i];
		return (0);
	}
	if (cmd_line[*i] == ' ')
		*i += skip_spaces(cmd_line, *i);
	if (cmd_line[*i] == '>' || cmd_line[*i] == '<' || end_of_cmd(cmd_line[*i]))
	{
		*stx_error = cmd_line[*i];
		return (0);
	}
	return (1);
}

int	second_check(char *cmd_line, int *i, int *stx_error)
{
	int	inc;

	if (*i != 0 && ft_isdigit(cmd_line[*i - 1]) && (cmd_line[*i - 2] == ' '
			|| end_of_cmd(cmd_line[*i])))
	{
		*stx_error = cmd_line[*i - 1];
		return (0);
	}
	inc = *i;
	if (cmd_line[*i + 1] == '<' && !heredoc_mode(cmd_line, i, stx_error))
		return (0);
	else
	{
		if (cmd_line[*i] == ' ' || inc == *i)
			*i += skip_spaces(cmd_line, *i);
		if (cmd_line[*i] == '>' || cmd_line[*i] == '<'
			|| end_of_cmd(cmd_line[*i]))
		{
			*stx_error = cmd_line[*i];
			return (0);
		}
	}
	return (1);
}
