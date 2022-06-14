
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
