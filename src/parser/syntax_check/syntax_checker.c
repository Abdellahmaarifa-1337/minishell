/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:13:09 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/14 10:46:39 by mkabissi         ###   ########.fr       */
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
			while (src[k + 1] && src[++k] && src[k] != '\'')
				p[i++] = 'A';
		else if (src[k] == '"')
			while (src[k + 1] && src[++k] && src[k] != '"')
				p[i++] = 'B';
		else
			p[i++] = src[k];
		k++;
	}
	p[i] = '\0';
	return (p);
}

void	print_err(int stx_error)
{
	if (stx_error == '\0' || stx_error == '\n')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putendl_fd("`newline'", 2);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write(2, &stx_error, 1);
		ft_putstr_fd("'\n", 2);
	}
}

int	syntax_checker(char *cmd_line)
{
	t_syntax_dt	*dt;

	dt = (t_syntax_dt *)malloc(sizeof(t_syntax_dt));
	if (!dt)
	{
		write(2, "(t_syntax_dt) dt: malloc error\n", 31);
		return (0);
	}
	dt->error = 0;
	dt->end = -1;
	if (!quotes_check(cmd_line, &dt->stx_error, &dt->end) && !dt->error)
		dt->error = 1;
	if (!pipe_check(cmd_line, dt))
		dt->error = 1;
	if (!redirect_check(cmd_line, &dt->stx_error, &dt->end) || dt->error)
	{
		print_err(dt->stx_error);
		return (0);
	}
	free(dt);
	return (1);
}
