/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:25:18 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/14 12:04:38 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	error_type(char *p, t_syntax_dt *dt)
{
	int	index;

	if (*p == '|' && *(p + 1) == '|')
	{
		index = (unsigned int)p + 1 - dt->first_address;
		if (index < dt->end || dt->end < 0)
		{
			dt->stx_error = *p;
			dt->end = index;
		}
		return (0);
	}
	index = (unsigned int)p - dt->first_address;
	if (index < dt->end || dt->end < 0)
	{
		dt->stx_error = *p;
		dt->end = index;
	}
	return (0);
}

int	no_problem(char *p, t_syntax_dt *dt)
{
	int	index;

	index = (unsigned int)p - dt->first_address;
	if (index < dt->end || dt->end < 0)
	{
		dt->stx_error = '\n';
		dt->end = index;
	}
	return (0);
}

int	body(char **p, t_syntax_dt *dt)
{
	while (*p && **p == ' ')
		++*p;
	if (dt->first_lap && dt->first_lap-- && **p == '|')
		return (error_type(*p, dt));
	*p = ft_strchr(*p, '|');
	if (*p)
		*p += 1;
	while (*p && **p == ' ')
		++*p;
	if (*p && **p == '\0')
		return (no_problem(*p, dt));
	else if (*p && (**p == '|' || **p == ';' || **p == '&'))
		return (error_type(*p, dt));
	return (1);
}

int	pipe_check(char *cmd_line, t_syntax_dt *dt)
{
	char	*line;
	char	*p;

	dt->first_lap = 1;
	line = skip_quote(cmd_line);
	p = line;
	dt->first_address = (unsigned int)p;
	while (p)
	{
		if (!body(&p, dt))
		{
			free(line);
			return (0);
		}
	}
	if (line)
		free(line);
	return (1);
}
