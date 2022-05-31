/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 14:57:16 by amaarifa          #+#    #+#             */
/*   Updated: 2021/11/10 16:37:30 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*search_str(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		n;

	i = 0;
	j = 0;
	n = 0;
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j])
			{
				if (++n > len)
					return (0);
				if (!needle[++j])
					return ((char *)(haystack + i));
			}
			n -= j;
		}
		n++;
		j = 0;
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*res;

	if (*needle == '\0')
		return ((char *)(haystack));
	res = search_str(haystack, needle, len);
	if (res)
		return (res);
	return (0);
}
