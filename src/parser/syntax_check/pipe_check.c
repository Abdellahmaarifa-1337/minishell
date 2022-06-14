/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:25:18 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/14 09:54:05 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	error_type(char *p, int *stx_error, unsigned int first_address, int *end)
{
	int	index;

	if (*p == '|' && *(p + 1) == '|')
	{
		index = (unsigned int)p + 1 - first_address;
		if (index < *end || *end < 0)
		{
			*stx_error = *p;
			*end = index;
		}
		return (0);
	}
	index = (unsigned int)p - first_address;
	if (index < *end || *end < 0)
	{
		*stx_error = *p;
		*end = index;
	}
	return (0);
}

int	no_problem(char *p, int *stx_error, unsigned int first_address, int *end)
{
	int	index;

	index = (unsigned int)p - first_address;
	if (index < *end || *end < 0)
	{
		*stx_error = '\n';
		*end = index;
	}
	return (0);
}

int	body(char **p, char *line, t_syntax_dt *dt)
{
	while (*p && **p == ' ')
		++*p;
	if (dt->first_lap && dt->first_lap-- && **p == '|')
	{
		free(line);
		return (error_type(*p, &dt->stx_error, dt->first_address, &dt->end));
	}
	*p = ft_strchr(*p, '|');
	if (*p)
		*p += 1;
	while (*p && **p == ' ')
		++*p;
	if (*p && **p == '\0')
	{
		free(line);
		return (no_problem(*p, &dt->stx_error, dt->first_address, &dt->end));
	}
	else if (*p && (**p == '|' || **p == ';' || **p == '&'))
	{
		free(line);
		return (error_type(*p, &dt->stx_error, dt->first_address, &dt->end));
	}
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
		if (!body(&p, line, dt))
			return (0);
	if (line)
		free(line);
	return (1);
}
