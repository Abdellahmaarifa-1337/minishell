/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:10:18 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 13:49:13 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*get_env(char *s)
{
	char	*str;

	str = ft_strdup(getenv(s));
	if (!str)
		return (ft_strdup(""));
	return (str);
}
