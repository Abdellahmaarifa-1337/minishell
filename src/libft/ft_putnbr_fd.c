/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:16:05 by amaarifa          #+#    #+#             */
/*   Updated: 2021/11/10 14:16:05 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int		res;
	char				c;

	if (n < 0)
	{
		res = n * -1;
		write(fd, "-", 1);
	}
	else
		res = n;
	if (res <= 9)
	{
		c = res + 48;
		write(fd, &c, 1);
	}
	if (res > 9)
	{
		ft_putnbr_fd(res / 10, fd);
		c = res % 10 + 48;
		write(fd, &c, 1);
	}
}
