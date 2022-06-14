/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:22:37 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/14 02:05:44 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_av(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
	{
		free(av[i]);
		i++;
	}
	if (av)
		free(av);
}

void	change_envpwd(t_env **env_lst, char *new_pwd, char *old_pwd)
{
	char	*new;
	char	*old;
	char	**tmp;

	if (!*env_lst)
		return ;
	new = ft_strjoin("export PWD=", new_pwd);
	old = ft_strjoin("export OLDPWD=", old_pwd);
	tmp = ft_split(new, ' ');
	ft_export(env_lst, tmp);
	free_av(tmp);
	tmp = ft_split(old, ' ');
	ft_export(env_lst, tmp);
	free_av(tmp);
	free(new);
	free(old);
}

void	put_error_message(char *dirname)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(dirname, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}

char	*ft_getenv(char *name, t_env **env_lst)
{
	t_env	*temp;

	if (!*env_lst || !name)
		return (NULL);
	temp = *env_lst;
	while (temp)
	{
		if (ft_strcmp(name, temp->key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

char	*get_directory_name(char *token, t_env **env_lst)
{
	char	*home;
	char	*rest_of_path;
	char	*temp;

	if (!token || ft_strncmp("~", token, 2) == 0)
		return (ft_getenv("HOME", env_lst));
	else if (ft_strncmp("~-", token, 3) == 0)
		return (ft_getenv("OLDPWD", env_lst));
	else if (ft_strncmp("-", token, 2) == 0)
	{
		temp = ft_getenv("OLDPWD", env_lst);
		ft_putendl_fd(temp, STDOUT_FILENO);
		return (temp);
	}
	else if (ft_strncmp("~/", token, 2) == 0)
	{
		home = ft_getenv("HOME", env_lst);
		rest_of_path = ft_substr(token, 1, ft_strlen(token) - 1);
		temp = ft_strjoin(home, rest_of_path);
		free(rest_of_path);
		return (temp);
	}
	else
		return (token);
}

void	cd(char **token, t_env **env_lst)
{
	char	buffer[PATH_MAX];
	char	*old_pwd;
	char	*dirname;
	DIR		*dir;

	old_pwd = ft_strdup(ft_getenv("PWD", env_lst));
	dirname = get_directory_name(token[1], env_lst);
	dir = opendir(dirname);
	if (dir)
	{
		closedir(dir);
		chdir(dirname);
		getcwd(buffer, PATH_MAX);
		char *tmp;
		tmp = ft_strdup(buffer);
		change_envpwd(env_lst, tmp, old_pwd);
		free(old_pwd);
		free(tmp);
	}
	else
	{
		g_exit_status = 1;
		put_error_message(dirname);
		free(old_pwd);
	}
}
