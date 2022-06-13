/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:48:45 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/13 16:36:10 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_tk(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		print_token(tokens[i]);
		printf("\n ------------------PIPE----------------- \n");
		i++;
	}
}

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

void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("The key : %s\n", tmp->key);
		printf("The value : %s\n", tmp->value);
		tmp = tmp->next;
	}
}

/* TEST BUILTINGS */
void	unset_test(t_env **env_lst, char **av, int ac)
{
	av[ac - 1] = NULL;
	printf("\n\nbefore unset \n\n");
	print_env(*env_lst);
	unset(env_lst, av);
	printf("\n\nafter unset \n\n");
	print_env(*env_lst);
	//exit(1);
}

// void env_test(t_env *env_list)
// {
// 	env(env_list);
// 	exit(1);
// }

void	export_test(t_env	**env, char **av, int ac)
{
	av[ac - 1] = 0;
	ft_export(env, NULL);
	printf("\n\nADDING VALUES\n\n");
	ft_export(env, av);
	ft_export(env, NULL);
	// exit(1);
}
/* SET TO DEFAULT */
int	g_exit_status = 0;

void	prompt(t_env **env_lst)
{
	t_cmd_list	*cmd_list;
	char		*line;
	int			keep_reading;
	int			n;

	keep_reading = 1;
	n = g_exit_status;

	
	
	while (keep_reading > 0 && g_exit_status >= 0)
	{
		signal(SIGINT, int_handler);
		signal(SIGQUIT, int_handler);
		// printf("value %d\n", g_exit_status);
		// if (g_exit_status < 0)
		// 	g_exit_status = (g_exit_status  + 1) * -1;
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
		cmd_list = init_cmd_list(line);
		cmd_list->exit = 0;
		add_history(line);
		cmd_list->env = env_lst;
		parser(cmd_list);
		execution(cmd_list, env_lst);
		// print_cmd_tk(cmd_list->tokens);
		// printf("exit: %d\n", cmd_list->exit);
		keep_reading -= cmd_list->exit;
		free_cmd_list(cmd_list);
		cmd_list = NULL;
	}
	//printf("g_exit_status %d\n", g_exit_status);
}

int	main(int ac, char **av, char **env)
{
	t_env		*env_lst;

	env_lst = set_env(env);
	(void)av;
	(void)ac;
	while (1)
	{
		prompt(&env_lst);
		if (g_exit_status < 0)
			g_exit_status = 1;
	}
	return (0);
}
