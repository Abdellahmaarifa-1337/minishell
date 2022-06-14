/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:38:51 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/14 02:53:06 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	replace_pipe(char *source, int i, char c)
{
	i++;
	if (!source[i])
		return (-1);
	while (source[i] && source[i] != c)
	{
		if (source[i] == '|')
			source[i] = -1;
		i++;
	}
	return (i);
}

void	flag_pipe(char *source)
{
	int	i;
	int	n;

	i = 0;
	while (source[i])
	{
		if (source[i] == '\'')
		{
			n = replace_pipe(source, i, '\'');
			if (n == -1)
				break ;
			i = n;
		}
		else if (source[i] == '\"')
		{
			n = replace_pipe(source, i, '\"');
			if (n == -1)
				break ;
			i = n;
		}
		i++;
	}
}

void	unflag_pipe(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == -1)
			s[i] = '|';
		i++;
	}
}

void	unflag_cmd_list(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		unflag_pipe(s[i]);
		i++;
	}
}
