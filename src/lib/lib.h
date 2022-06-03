/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:09:49 by amaarifa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/06/02 15:03:38 by mkabissi         ###   ########.fr       */
=======
/*   Updated: 2022/06/02 07:21:45 by amaarifa         ###   ########.fr       */
>>>>>>> 69fd0caff08e0f59731e77cdbf449a926d215ba4
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "../../types.h"

t_env	*set_env(char **env);
t_env	*create_env(char *s);
<<<<<<< HEAD
// char	*get_env(t_env *env_list, char *key);
=======
char	*get_env(t_env *env_list, char *key);
int		get_index_char(char *s, char c);
>>>>>>> 69fd0caff08e0f59731e77cdbf449a926d215ba4

#endif