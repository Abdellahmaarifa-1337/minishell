/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:00:15 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/13 23:01:08 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path && path[i])
	{
		free(path[i]);
		i++;
	}
	if (path)
		free(path);
}

void	free_args(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
	{
		free(av[i]);
		i++;
	}
	if (av)
		free(av);
}
