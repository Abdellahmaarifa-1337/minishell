/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:06:13 by amaarifa          #+#    #+#             */
/*   Updated: 2021/11/10 15:44:34 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		size;
	char	*str;
	int		i;

	if (!s || !f)
		return (0);
	i = 0;
	size = ft_strlen(s);
	str = (char *)malloc((sizeof(char) * (size + 1)));
	if (!str)
		return (str);
	while (i < size)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
