/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:48:13 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/13 23:40:00 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	heredoc_handler(int signal)
{
	(void)signal;
	close(0);
	if (g_exit_status >= 0)
		g_exit_status = -1 * (g_exit_status + 1);
}

static void	open_heredoc(char *limiter)
{
	char	*s;

	if (g_exit_status < 0)
		return ;
	s = readline("> ");
	while (s && ft_strncmp(s, limiter, ft_strlen(limiter) + 1) != 0)
	{
		if (s)
			free(s);
		s = readline("> ");
	}
	if (s)
		free(s);
	return ;
}

static void	open_here_doc(t_token	*tokens)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
			open_heredoc(tmp->value);
		i++;
		tmp = tmp->next;
	}
}

static void	exec_here_doc(t_cmd_list *cmd_lst)
{
	int	i;
	int	saved;

	saved = dup(0);
	i = 0;
	signal(SIGINT, heredoc_handler);
	while ((cmd_lst->tokens)[i])
	{
		open_here_doc((cmd_lst->tokens)[i]);
		i++;
	}
	dup2(saved, 0);
	signal(SIGINT, int_handler);
}

int	execute_heredoc(t_syntax_dt *dt, char *cmd_line)
{
	t_cmd_list	*cmd_lst;
	char		*line;
	int			lenght;

	lenght = 0;
	while (cmd_line[lenght] && lenght < dt->end)
		lenght++;
	line = ft_substr(cmd_line, 0, lenght - 1);
	cmd_lst = init_cmd_list(line);
	parser(cmd_lst);
	exec_here_doc(cmd_lst);
	free_cmd_list(cmd_lst);
	return (1);
}
