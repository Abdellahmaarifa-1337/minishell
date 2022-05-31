/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:23:04 by amaarifa          #+#    #+#             */
/*   Updated: 2021/11/10 14:25:37 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				size;
	unsigned char	*str;

	str = (unsigned char *)s;
	size = ft_strlen((const char *)str);
	while (size >= 0)
	{
		if (str[size] == (unsigned char)c)
			return ((char *)&str[size]);
		size--;
	}
	return (0);
}
