/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:22:37 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/02 15:10:15 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	change_envpwd(t_env *env_lst, char *new_pwd, char *old_pwd)
{
	char	*p;

	p = ft_strjoin("export PWD=", new_pwd);
	export(&env_lst, &p);
	free(p);
	free(new_pwd);
	p = ft_strjoin("export PWD=", old_pwd);
	export(&env_lst, &p);
	free(p);
	free(old_pwd);
}

void cd(char **token, t_env *env_lst)
{
	char	buffer[PATH_MAX];
	char	*old_pwd;
	char	*dirname;
	DIR		*dir;
	int		dir_exists = 0;

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
		perror("cd error");
	free(old_pwd);
	return ;
}