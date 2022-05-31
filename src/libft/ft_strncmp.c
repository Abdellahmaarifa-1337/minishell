/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:54:11 by amaarifa          #+#    #+#             */
/*   Updated: 2021/11/10 15:47:02 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char	*s1, const char	*s2, size_t	n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (a[i] && b[i] && a[i] == b[i] && i < n - 1)
		i++;
	return (a[i] - b[i]);
}
