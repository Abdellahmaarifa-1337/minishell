/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:58:55 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/03 11:31:38 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_the_last_out(t_token *tokens, int index)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
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
	if (s)
		free(s);
}

char	*generate_unique_name(int id)
{
	char	*id_str;
	char	*name;

	id_str = ft_itoa(id);
	name = ft_strjoin("/tmp/here_doc_", id_str);
	free(id_str);
	return (name);
}

char	*append_string(char *res, char *s)
{
	char	*tmp;
	char	*new_res;

	new_res = ft_strjoin(res, s);
	free(res);
	free(s);
	tmp = new_res;
	new_res = ft_strjoin(tmp, "\n");
	free(tmp);
	return (new_res);
}

void	open_full_here_doc(t_token *token, int id, t_env *env_lst)
{
	char	*s;
	char	*res;
	int		fd;
	char	*name;

	(void)env_lst;
	name = generate_unique_name(id);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	res = ft_strdup("");
	s = readline(">");
	while (!s || ft_strncmp(s, token->value, ft_strlen(token->value) + 1) != 0)
	{
		if (s)
		{
			res = append_string(res, s);
		}
		s = readline(">");
	}
	if (s)
		free(s);
	if (res && res[0])
		write(fd, res, ft_strlen(res));
	token->type = IN_REDERCTIONT;
	free(token->value);
	token->value = name;
	free(res);
}

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

	i = 0;
	while ((cmd_lst->tokens)[i])
	{
		open_here_doc((cmd_lst->tokens)[i], i, env_lst);
		i++;
	}
}
