/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:15:10 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/02 08:11:57 by amaarifa         ###   ########.fr       */
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

void	builtins(char **token);
void	ft_echo(char **token);
void	ft_pwd(void);
void	unset(t_env **env, char **av);
void	env(t_env *env);
void	cd(char **token, t_env *env);
void	export(t_env **env, char **av);
void	export_print(t_env *env);
int		is_valid_idn(char *s);

#endif