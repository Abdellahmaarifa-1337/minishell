/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:15:10 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/30 14:58:50 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../../types.h"
# include "../lib/lib.h"

int		unset(t_env **env, char **av);
int		env(t_env *env);
int		export(t_env **env, char **av);
void	export_print(t_env *env);
int		is_valid_idn(char *s);
#endif