/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:05:27 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/13 23:07:59 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../builtins/builtins.h"
# include "../../types.h"
# include "../libft/libft.h"
# include "../lib/lib.h"
# include "../builtins/builtins.h"
# include <errno.h>

/**************** EXECUTIONS PARTS *****************/
void	exec_single_cmd(t_cmd_list *cmd_lst, t_env **env_lst);
void	exec_multiple_cmds(t_cmd_list *cmd_lst, t_env **env_lst, t_data *dt);

/******************** HELPERS **********************/
char	**get_args(t_token **tokens);
int		resolve_path(char **args, t_env **env_lst, int exit_process);
void	exec_here_doc(t_cmd_list *cmd_lst, t_env *env_lst);
int		*get_in_out_file(t_token *tokens, int *fd, int exit_process);
char	*expand_var(char *value, t_env **env_lst);
void	ft_close(int **fd, int size, int fd1, int fd2);
void	ft_free(void **arr, int size);
void	free_path(char **path);
void	free_args(char **av);
char	*expand_str(char *s, t_env	**env_lst);
void	return_all_quotes(char *s);
void	hide_all_quotes(char *s);
char	*append_string(char *res, char *s);
char	*generate_unique_name(char *path, int id);
void	open_full_here_doc(t_token *token, int id, t_env *env_lst);
void	run_read_line(char	**s, char **res, t_token *token, t_env **env_lst);
void	open_empty_here_doc(char *limiter);
void	handler(int signal);
int		is_the_last_out(t_token *tokens, int index);
#endif