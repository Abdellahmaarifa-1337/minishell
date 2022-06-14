/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:04:58 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/13 23:05:12 by amaarifa         ###   ########.fr       */
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

void	handler(int signal)
{
	(void)signal;
	close(0);
	if (g_exit_status >= 0)
		g_exit_status = -1 * (g_exit_status + 1);
}

void	open_empty_here_doc(char *limiter)
{
	char	*s;

	if (g_exit_status < 0)
		return ;
	s = readline(">");
	while (s && ft_strncmp(s, limiter, ft_strlen(limiter) + 1) != 0)
	{
		if (s)
			free(s);
		s = readline(">");
	}
	if (s)
		free(s);
}

void	run_read_line(char	**s, char **res, t_token *token, t_env **env_lst)
{
	*s = readline("<");
	while (*s && ft_strncmp(*s, token->value, ft_strlen(token->value) + 1) != 0)
	{
		if (*s)
		{
			if (token->expand_heredoc)
				*res = append_string(*res, expand_str(*s, env_lst));
			else
				*res = append_string(*res, *s);
		}
		*s = readline("<");
	}
}

void	open_full_here_doc(t_token *token, int id, t_env *env_lst)
{
	char	*s;
	char	*res;
	int		fd;
	char	*name;

	name = generate_unique_name("/tmp/here_doc_", id);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	res = ft_strdup("");
	if (g_exit_status < 0)
		return ;
	run_read_line(&s, &res, token, &env_lst);
	if (s)
		free(s);
	if (res && res[0])
		write(fd, res, ft_strlen(res));
	token->type = IN_REDERCTIONT;
	free(token->value);
	token->value = name;
	free(res);
}
