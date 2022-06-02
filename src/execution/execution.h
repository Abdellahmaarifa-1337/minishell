/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:05:27 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/02 19:13:32 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../builtins/builtins.h"
# include "../../types.h"
# include "../libft/libft.h"
# include "../lib/lib.h"
# include "../builtins/builtins.h"

char	**get_args(t_token **tokens);
void	resolve_path(char **args, t_env **env_lst);
void	exec_here_doc(t_cmd_list *cmd_lst);
#endif