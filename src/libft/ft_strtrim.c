/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:01:17 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 13:49:56 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	is_in(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	get_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (is_in(s1[i], set))
		i++;
	return (i);
}

static int	get_end(char const *s1, char const *set)
{
	int	size;

	size = ft_strlen(s1) - 1;
	while (is_in(s1[size], set) && size != 0)
		size--;
	return (size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*s;
	size_t	i;

	if (!s1)
		return (0);
	i = 0;
	start = get_start(s1, set);
	end = get_end(s1, set);
	if (start >= ft_strlen(s1) || end == 0)
		return (ft_strdup(s1));
	s = (char *)malloc((end - start + 2) * sizeof(unsigned char));
	if (!s)
		return (0);
	while (start <= end)
	{
		s[i] = s1[start];
		start++;
		i++;
	}
	s[i] = '\0';
	return (s);
}
