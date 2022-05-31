/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:25:18 by mkabissi          #+#    #+#             */
/*   Updated: 2022/05/30 13:46:19 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	error_type(char *p, int *stx_error)
{
	if (*p == '|' && *(p + 1) == '|')
		return (2);
	*stx_error = *p;
	return (1);
}

int	pipe_check(char *cmd_line, int *stx_error)
{
	char	*p;
	int		first_lap;

	first_lap = 1;
	p = cmd_line;
	while (p)
	{
		while (p && *p == ' ')
			p++;
		if (first_lap && first_lap-- && *p == '|')
			return (error_type(p, stx_error));
		p = ft_strchr(p, '|');
		if (p)
			p += 1;
		while (p && *p == ' ')
			p++;
		if (p && *p == '\0')
			return (0);
		else if (p && (*p == '|' || *p == ';' || *p == '&'))
			return (error_type(p, stx_error));
	}
	return (3);
}
