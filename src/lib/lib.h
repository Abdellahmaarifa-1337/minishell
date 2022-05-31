/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:09:49 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/31 12:17:20 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "../../types.h"

t_env	*set_env(char **env);
t_env	*create_env(char *s);
char	*get_env(t_env *env_list, char *key);

#endif