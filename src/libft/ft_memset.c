/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 07:06:32 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 21:18:28 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t		i;
	char		*s;

	i = 0;
	s = (char *)b;
	while (i < len)
	{
		s[i] = c;
		i++;
	}
	return (s);
}
