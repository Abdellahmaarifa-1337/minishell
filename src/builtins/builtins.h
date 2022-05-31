/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:15:10 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/30 21:59:39 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <limits.h>
# include <dirent.h>
# include "../../types.h"

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
int		unset(t_env **env, char **av);
int		env(t_env *env);
void 	cd(char **token, t_env *env);
int		export(t_env **env, char **av);

#endif