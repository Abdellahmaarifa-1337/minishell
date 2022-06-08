/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:22:37 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/08 04:20:31 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	change_envpwd(t_env *env_lst, char *new_pwd, char *old_pwd)
{
	char	*new;
	char	*old;

	new = ft_strjoin("export PWD=", new_pwd);
	old = ft_strjoin("export OLDPWD=", old_pwd);
	ft_export(&env_lst, ft_split(new, ' '));
	ft_export(&env_lst, ft_split(old, ' '));
	free(new);
	free(old);
	free(new_pwd);
	free(old_pwd);
}

void cd(char **token, t_env *env_lst)
{
	char	buffer[PATH_MAX];
	char	*old_pwd;
	char	*dirname;
	DIR		*dir;

	old_pwd = ft_strdup(getcwd(buffer, PATH_MAX));
	if (!token[1])
		dirname = getenv("HOME");
	else
		dirname = token[1];
	dir = opendir(dirname);
	if (dir)
	{
		closedir(dir);
		chdir(dirname);
		getcwd(buffer, PATH_MAX);
		change_envpwd(env_lst, ft_strdup(buffer), old_pwd);
	}
	else
	{
		perror("cd error");
		free(old_pwd);
	}
	if (!dirname)
		free(dirname);
	return ;
}