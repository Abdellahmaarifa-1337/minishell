/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:09:22 by amaarifa          #+#    #+#             */
/*   Updated: 2021/11/11 14:26:11 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t			d_size;
	size_t			s_size;
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !dstsize)
		return (ft_strlen(src));
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	d_size = ft_strlen(dest);
	s_size = ft_strlen(src);
	i = 0;
	if (dstsize <= d_size)
		return (dstsize + s_size);
	if (dstsize != 0)
	{
		while (s[i] && i < (dstsize - d_size - 1))
		{
			d[d_size + i] = s[i];
			i++;
		}
		d[d_size + i] = '\0';
	}
	return (d_size + s_size);
}
