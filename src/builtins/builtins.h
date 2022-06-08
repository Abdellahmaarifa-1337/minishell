/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:15:10 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/08 12:05:29 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <limits.h>
# include <dirent.h>
# include "../../types.h"
# include "../lib/lib.h"

# define ECHO 6
# define CD 7
# define PWD 8
# define EXPORT 9
# define UNSET 10
# define ENV 11
# define EXIT 12

/********** BUILTINS **********/

void	execute_command(char **args, t_env *env_lst, int *exit, int multi_cmds);
void	echo(char **token);
void	pwd(void);
void	unset(t_env **env, char **av);
void	env(t_env *env);
void	cd(char **token, t_env *env);
void	ft_export(t_env **env_lst, char **av);
void	ft_exit(char **args, int *exit);
void	export_print(t_env *env);
int		is_valid_idn(char *s);
int		which_builtin(char *builtin);
char	**env_convert(t_env *env_lst);
#endif