/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:58:55 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/02 20:29:27 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_the_last_out(t_token *tokens, int index)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	//printf("index is %d\n", index);
	while (tmp)
	{
		if (i > index && (tmp->type == HERE_DOC
				|| tmp->type == IN_REDERCTIONT))
			return (0);
		i++;
		tmp = tmp->next;
	}
	if (i == index)
		return (1);
	return (1);
}

void	open_empty_here_doc(char *limiter)
{
	char	*s;

	s = readline(">");
	while (!s || ft_strncmp(s, limiter, ft_strlen(limiter) + 1) != 0)
	{
		if (s)
			free(s);
		s = readline(">");
	}
}

void	open_full_here_doc(t_token *token)
{
	char	*s;
	char	*res;
	char	*tmp;
	int		fd;

	fd = open("/tmp/t1", O_CREAT | O_RDWR, 0777);
	res = ft_strdup("");
	s = readline(">");
	while (!s || ft_strncmp(s, token->value, ft_strlen(token->value) + 1) != 0)
	{
		if (s)
		{
			tmp = res;
			res = ft_strjoin(tmp, s);
			free(tmp);
			free(s);
		}
		s = readline(">");
	}
	if (res && res[0])
	{
		write(fd, res, ft_strlen(res));
	}
}

void	open_here_doc(t_token	*tokens)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			// get_here_doc_data(tmp->value);
			if (is_the_last_out(tokens, i))
				open_full_here_doc(tmp);
			else
				open_empty_here_doc(tmp->value);
		}
		i++;
		tmp = tmp->next;
	}
}

void	exec_here_doc(t_cmd_list *cmd_lst)
{
	int	i;

	i = 0;
	while ((cmd_lst->tokens)[i])
	{
		open_here_doc((cmd_lst->tokens)[i]);
		i++;
	}
}
