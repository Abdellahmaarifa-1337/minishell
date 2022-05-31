/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 12:10:26 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 20:59:49 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char	*str)
{
	int				i;
	int				ng;
	unsigned long	res;
	unsigned long	l_max;

	i = 0;
	ng = 1;
	l_max = 9223372036854775807;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		ng *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i++] - '0');
		if (res >= l_max && ng > 0)
			return (-1);
		else if (res > l_max && ng < 0)
			return (0);
	}
	return (res * ng);
}
