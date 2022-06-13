/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_idn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:51:32 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/13 14:17:15 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	is_valid_idn(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (s[0] && !ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	while (s[i])
	{
		if (ft_isalnum(s[i]) || s[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}
