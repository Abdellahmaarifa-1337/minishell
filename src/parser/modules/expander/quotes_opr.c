/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_opr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:11:22 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 15:21:27 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

int	unclosed_double_qoutes(char *s, int i)
{
	int		j;
	int		n;

	n = 0;
	j = 0;
	while (s[j] && j <= i)
	{
		if (s[j] == '\"')
			n = !n;
		j++;
	}
	return (n);
}

void	hide_wrapped_quotes(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
	{
		if (s[*i] == '\'')
			s[*i] = -1;
		else if (s[*i] == '\"')
			s[*i] = -2;
		(*i)++;
	}
}

void	hide_quotes(char	*s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			hide_wrapped_quotes(s, &i, '\'');
		else if (s[i] == '\"')
			hide_wrapped_quotes(s, &i, '\"');
		i++;
	}
}
