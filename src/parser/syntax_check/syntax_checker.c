/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:13:09 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/14 02:56:27 by amaarifa         ###   ########.fr       */
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
	while (cmd_line[k + 1] && cmd_line[++k] == ' ')
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
			while (src[k + 1] && src[++k] != '\'' && p[i + 1])
				p[i++] = 'A';
		else if (src[k] == '"')
			while (src[k + 1] && src[++k] != '"' && p[i + 1])
				p[i++] = 'B';
		else
			p[i++] = src[k];
		k++;
	}
	p[i] = '\0';
	return (p);
}

void print_char_err(char	*s1, char c, char *s2)
{
	ft_putstr_fd(s1, 2);
	write(2, &c, 1);
	ft_putstr_fd(s2, 2);
}

int	syntax_checker(char *cmd_line)
{
	t_syntax_dt	*dt;

	dt = (t_syntax_dt *)malloc(sizeof(t_syntax_dt));
	dt->error = 0;
	dt->end = -1;
	if (!quotes_check(cmd_line, &dt->stx_error, &dt->end) && !dt->error)
	{
		dt->error = 1;
	}
	dt->pipe_error = pipe_check(cmd_line, &dt->stx_error, &dt->end);
	if ((dt->pipe_error == 0 || dt->pipe_error == 1 || dt->pipe_error == 2)
		&& !dt->error)
	{
		if (dt->pipe_error == 0)
			ft_putstr_fd("minishell: unclosed pipe\n", 2);
		else if (dt->pipe_error == 1)
			print_char_err("minishell: syntax error near unexpected token `",
				dt->stx_error, "'\n");
		else if (dt->pipe_error == 2)
			ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
		dt->error = 1;
	}
	if ((!redirect_check(cmd_line, &dt->stx_error, &dt->end) || dt->error))
		return (0);
	free(dt);
	return (1);
}

