/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:02:39 by amaarifa          #+#    #+#             */
/*   Updated: 2021/11/10 14:12:32 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char			*str;
	size_t					i;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == ((unsigned char)c))
			return (str + i);
		i++;
	}
	return (0);
}
