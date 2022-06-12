/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:00:37 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/12 09:24:58 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd(void)
{
	char	buffer[PATH_MAX];

	g_exit_status = 0;
	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		g_exit_status = 1;
		perror("getcwd() error");
	}
	ft_putendl_fd(buffer, 1);
	return ;
}
