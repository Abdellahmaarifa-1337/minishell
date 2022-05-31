/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:13:09 by mkabissi          #+#    #+#             */
/*   Updated: 2022/05/25 15:19:27 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	end_of_cmd(char c)
{
	if (c == '|' || c == ';' || c == '&' || c == '#' || c == '\0' || c == '\n')
		return (1);
	return (0);
}

int	skip_spaces(char *cmd_line, int i)
{
	int	k;
	int	skip;

	k = i;
	skip = 1;
	while (cmd_line[++k] == ' ')
		skip++;
	return (skip);
}

char	*skip_quote(char *src)
{
	char	*p;
	long	i;
	long	k;

	i = 0;
	k = 0;
	p = (char *)(malloc(sizeof(char) * (ft_strlen(src) + 1)));
	if (p == NULL)
		return (NULL);
	while (src[k])
	{
		if (src[k] == '\'')
			while (src[++k] != '\'')
				p[i++] = 'A';
		else if (src[k] == '"')
			while (src[++k] != '"')
				p[i++] = 'B';
		else
			p[i++] = src[k];
		k++;
	}
	p[i] = '\0';
	return (p);
}

int	redirect_check(char *cmd_line, int *stx_error)
{
	char	*p;

	p = skip_quote(cmd_line);
	if (p && !redirection_check(p, stx_error))
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

int	syntax_checker(char *cmd_line)
{
	int	pipe_error;
	int	stx_error;

	if (!quotes_check(cmd_line, &stx_error))
	{
		printf("minishell: unclosed quote (%c)\n", stx_error);
		return (0);
	}
	pipe_error = pipe_check(cmd_line, &stx_error);
	if (pipe_error == 0 || pipe_error == 1 || pipe_error == 2)
	{
		if (pipe_error == 0)
			printf("minishell: unclosed pipe\n");
		else if (pipe_error == 1)
			printf("minishell: syntax error near unexpected token `%c'\n",
				stx_error);
		else if (pipe_error == 2)
			printf("minishell: syntax error near unexpected token `||'\n");
		return (0);
	}
	if (!redirect_check(cmd_line, &stx_error))
		return (0);
	return (1);
}
