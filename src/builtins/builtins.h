/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:15:10 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/14 20:35:14 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <limits.h>
# include <dirent.h>
# include <sys/errno.h>
# include "../../types.h"
# include "../lib/lib.h"

# define _ECHO 6
# define CD 7
# define PWD 8
# define EXPORT 9
# define UNSET 10
# define ENV 11
# define EXIT 12

/********** BUILTINS **********/

void	execute_command(char **args, t_env **env_lst, t_cmd_list *cmd_lst,
			int multi_cmds);
void	echo(char **token);
void	pwd(void);
void	unset(t_env **env, char **av);
void	env(t_env *env, char **args);
void	cd(char **token, t_env **env);
void	ft_export(t_env **env_lst, char **av);
void	ft_exit(char **args, t_cmd_list *cmd_lst, int print);
char	*ft_getenv(char *name, t_env **env_lst);
void	export_print(t_env *env);
int		is_valid_idn(char *s);
int		which_builtin(char *builtin);
char	**env_convert(t_env *env_lst);
int		get_size_of_arr(void **tokens);
int		get_size_of_arr(void **tokens);
void	free_env(char **env);
#endif
