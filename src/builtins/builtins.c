/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:20:45 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/09 13:03:36 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	get_size_of_arr(void **tokens)
{
	int	len;

	len = 0;
	while (tokens && tokens[len])
		len++;
	return (len);
}

int	ft_special_cmp(char	*s1, char	*s2, size_t	n)
{
	unsigned char	*a;
	unsigned char	*b;
	char			*lowercase;
	size_t			i;

	lowercase = ft_strdup(s1);
	a = (unsigned char *)lowercase;
	b = (unsigned char *)s2;
	i = 0;
	while (a[i])
	{
		a[i] = ft_tolower(a[i]);
		i++;
	}
	if (n == 0)
	{
		free(lowercase);
		return (0);
	}
	i = 0;
	while (a[i] && b[i] && a[i] == b[i] && i < n - 1)
		i++;
	free(lowercase);
	return (a[i] - b[i]);
}

int	which_builtin(char *builtin)
{
	if (ft_special_cmp(builtin, "echo", 5) == 0)
		return (ECHO);
	else if (ft_strncmp(builtin, "cd", 3) == 0)
		return (CD);
	else if (ft_special_cmp(builtin, "pwd", 4) == 0)
		return (PWD);
	else if (ft_strncmp(builtin, "export", 7) == 0)
		return (EXPORT);
	else if (ft_strncmp(builtin, "unset", 6) == 0)
		return (UNSET);
	else if (ft_special_cmp(builtin, "env", 4) == 0)
		return (ENV);
	else if (ft_strncmp(builtin, "exit", 5) == 0)
		return (EXIT);
	return (-1);
}

void	exec(char **args, t_env **env_lst)
{
	(void)env_lst;	/********** REMOVE THIS SHIT ***********/
	char	**env;

	env = NULL;
	env = env_convert(*env_lst);
	execve(args[0], args, env);		/********* ENV. NOT SET YET **********/
}

void	execute_command(char **args, t_env **env_lst, t_cmd_list *cmd_lst, int multi_cmds)
{
	int	flag;
	(void)multi_cmds;
	flag = which_builtin(args[0]);
	if (flag == ECHO)
		echo(args);
	else if (flag == CD)
		cd(args, env_lst);
	else if (flag == PWD)
		pwd();
	else if (flag == EXPORT)
		ft_export(env_lst, args);
	else if (flag == UNSET)
		unset(env_lst, args);
	else if (flag == ENV)
		env(*env_lst);
	else if (flag == EXIT)
		ft_exit(args, cmd_lst);
	else
	{
		exec(args, env_lst);
	}

}
