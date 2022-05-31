/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 09:04:25 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/28 17:53:59 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char	*src)
{
	int		i;
	char	*p;

	i = 0;
	if (!src)
		return (NULL);
	p = (char *)(malloc(sizeof(char) * (ft_strlen(src) + 1)));
	if (p == NULL)
		return (NULL);
	while (src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
