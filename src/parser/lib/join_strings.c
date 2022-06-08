/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:07:06 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/08 13:09:01 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*join_strings(char *s1, char *s2)
{
	char	*s;

	s = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (s);
}
