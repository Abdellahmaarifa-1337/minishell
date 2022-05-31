/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 07:59:27 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 13:42:56 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../parser.h"

void	print_token(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		printf("------------token------------\n");
		printf("value	:	%s\n", temp->value);
		printf("type	:	%d\n", temp->type);
		printf("--------end of token--------\n");
		temp = temp->next;
	}
}
