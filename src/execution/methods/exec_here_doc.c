/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:58:55 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/13 23:05:21 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	open_here_doc(t_token	*tokens, int id, t_env *env_lst)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			if (is_the_last_out(tokens, i))
				open_full_here_doc(tmp, id, env_lst);
			else
				open_empty_here_doc(tmp->value);
		}
		i++;
		tmp = tmp->next;
	}
}

void	exec_here_doc(t_cmd_list *cmd_lst, t_env *env_lst)
{
	int	i;
	int	saved;

	i = 0;
	signal(SIGINT, handler);
	saved = dup(0);
	while ((cmd_lst->tokens)[i])
	{
		open_here_doc((cmd_lst->tokens)[i], i, env_lst);
		i++;
	}
	dup2(saved, 0);
	signal(SIGINT, int_handler);
}
