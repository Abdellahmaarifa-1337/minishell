/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:48:45 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/02 13:26:36 by amaarifa         ###   ########.fr       */
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

void env_test(t_env *env_list)
{
	env(env_list);
	exit(1);
}

void	export_test(t_env	**env, char **av, int ac)
{
	av[ac - 1] = 0;
	export(env, NULL);
	printf("\n\nADDING VALUES\n\n");
	export(env, av);
	export(env, NULL);
	exit(1);
}
/* SET TO DEFAULT */
int	g_exit_status = 0;

int	main(int ac, char **av, char **env)
{
	t_cmd_list	*cmd_list;
	char		*line;
	t_env		*env_lst;

	env_lst = set_env(env);
	(void)av;
	(void)ac;
	//unset_test(&env_lst, av, ac); //TEST UNSET
	// export_test(&env_lst, av, ac);

	//env_test(env_lst);
	while (1)
	{
		line = readline("minishell$ ");
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (!syntax_checker(line))
		{
			free(line);
			continue ;
		}
		cmd_list = init_cmd_list(line);
		add_history(line);
		cmd_list->env = &env_lst;
		parser(cmd_list);
		execution(cmd_list);
		print_cmd_tk(cmd_list->tokens);
		free_cmd_list(cmd_list);
		cmd_list = NULL;
	}
	return (0);
}
