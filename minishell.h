/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:49:19 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/14 20:41:31 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 *
 * @name Minishell
 *
 * @brief a simple shell programme.
 *
 * @author Abdellah maarifa & mohamed ilyas kabissi
 * 
 */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "types.h"							/*	Types, Structs definations	*/
# include "src/parser/parser.h"				/*	Parser Modules and methods	*/
# include "src/lib/lib.h"
# include "src/builtins/builtins.h"

void	parser(t_cmd_list	*cmd_list);
void	execution(t_cmd_list *cmd_lst, t_env **env_lst);

/********* TEMP FUNCTIONS **********/

void	print_token(t_token *token);
void	print_cmd_list(t_cmd_list *cmd_list);
int		g_exit_status;
#endif
