/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:48:45 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/14 20:44:06 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_cmd_list	*cmd_list)
{
	int		i;

	i = 0;
	if (!cmd_list)
		return ;
	free(cmd_list->source);
	free(cmd_list->cmd_line);
	if (cmd_list->tokens)
	{
		while ((cmd_list->tokens)[i])
		{
			delete_token((cmd_list->tokens) + i);
			(cmd_list->tokens)[i] = NULL;
			i++;
		}
		free(cmd_list->tokens);
	}
	free(cmd_list);
}

t_cmd_list	*init_cmd_list(char *s)
{
	t_cmd_list	*cmd_list;

	cmd_list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!cmd_list)
		exit(1);
	cmd_list->cmd_line = s;
	cmd_list->source = ft_strtrim(cmd_list->cmd_line, " ");
	cmd_list->tokens = NULL;
	cmd_list->env = NULL;
	if (!cmd_list->source)
		exit(1);
	return (cmd_list);
}

void	run_cmd(t_env **env_lst, int *keep_reading, char *line)
{
	t_cmd_list	*cmd_list;

	cmd_list = init_cmd_list(line);
	cmd_list->exit = 0;
	cmd_list->env = env_lst;
	parser(cmd_list);
	execution(cmd_list, env_lst);
	*keep_reading -= cmd_list->exit;
	free_cmd_list(cmd_list);
	cmd_list = NULL;
}

void	prompt(t_env **env_lst)
{
	char		*line;
	int			keep_reading;

	keep_reading = 1;
	while (keep_reading > 0 && g_exit_status >= 0)
	{
		signal(SIGINT, int_handler);
		signal(SIGQUIT, int_handler);
		line = readline("minishell$ ");
		if (!line)
			exit(0);
		if (line[0])
			add_history(line);
		if (line[0] == '\0' || !syntax_checker(line))
		{
			g_exit_status = 0;
			free(line);
			continue ;
		}
		add_history(line);
		run_cmd(env_lst, &keep_reading, line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env			*env_lst;
	struct termios	termios_new;

	env_lst = set_env(env);
	(void)av;
	(void)ac;
	g_exit_status = 0;
	while (1)
	{
		tcgetattr(0, &termios_new);
		termios_new.c_lflag &= ~ECHOCTL;
		tcsetattr(0, 0, &termios_new);
		prompt(&env_lst);
		if (g_exit_status < 0)
			g_exit_status = 1;
	}
	return (0);
}
