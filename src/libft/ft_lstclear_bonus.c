/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:50:35 by amaarifa          #+#    #+#             */
/*   Updated: 2021/11/13 08:42:10 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*next;

	if (*lst == NULL || !del)
		return ;
	temp = *lst;
	next = *lst;
	while (temp)
	{
		temp = temp->next;
		ft_lstdelone(next, del);
		next = temp;
	}
	*lst = NULL;
}
