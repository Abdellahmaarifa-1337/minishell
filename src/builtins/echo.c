/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:19:02 by mkabissi          #+#    #+#             */
/*   Updated: 2022/05/30 13:51:18 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_n_option(char *arg)
{
	long	option_len;
	long	k;

	option_len = strlen(arg);
	k = 1;
	while (option_len > 2 && ++k < option_len)
	{
		if (arg[k] != 'n' && arg[k] != '\0')
			return (0);
	}
	return (1);
}

void	ft_echo(char **token)
{
	int		n_option;
	long	i;

	i = 0;
	n_option = 0;
	while (token[++i] != NULL)
	{
		if (strncmp(token[i], "-n", 2) == 0
			&& check_n_option(token[i]))
				n_option = 1;
		else
			break ;
	}
	while (token[i])
	{
		ft_putstr_fd(token[i++], 1);
		if (token[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (n_option == 0)
		write(1, "\n", 1);
}
