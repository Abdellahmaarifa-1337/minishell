/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:25:18 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/13 23:19:18 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	error_type(char *p, int *stx_error, unsigned int first_address, int *end)
{
	int	index;

	if (*p == '|' && *(p + 1) == '|')
		return (2);
	*stx_error = *p;
	index = (unsigned int)p - first_address;
	if (index < *end || *end < 0)
		*end = index;
	return (1);
}

int	no_problem(char *p, unsigned int first_address, int *end)
{
	int				index;

	index = (unsigned int)p - first_address;
	if (index < *end || *end < 0)
		*end = index;
	return (0);
}

int	pipe_check(char *cmd_line, int *stx_error, int *end)
{
	unsigned int	first_address;
	char			*p;
	int				first_lap;

	first_lap = 1;
	p = cmd_line;
	first_address = (unsigned int)p;
	while (p)
	{
		while (p && *p == ' ')
			p++;
		if (first_lap && first_lap-- && *p == '|')
			return (error_type(p, stx_error, first_address, end));
		p = ft_strchr(p, '|');
		if (p)
			p += 1;
		while (p && *p == ' ')
			p++;
		if (p && *p == '\0')
			return (no_problem(p, first_address, end));
		else if (p && (*p == '|' || *p == ';' || *p == '&'))
			return (error_type(p, stx_error, first_address, end));
	}
	return (3);
}
