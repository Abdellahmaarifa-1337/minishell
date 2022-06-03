/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:22:38 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/03 17:25:22 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../../types.h"
# include "../lib/lib.h"

/*---------------------- MODULES -----------------------*/

/*------------------- Scanner Module -------------------*/

int				go_to_next_peer(t_token_source *token_source, char character);
t_token			*collect_string(t_token_source *token_source, int type);
t_token			*get_next_token(t_token_source *token_source, char symbol,
					int type1, int type2);
void			resolve_type(char symbol, int *type);

/*------------------- Expander Module -------------------*/
char			*expand_var(char *value, t_env **env_lst);
int				collect_var(char	*value, int *i, char **s, t_env **env_lst);
void			collect_none_var(char	*value, int *i, char **s);
void			expand_env_var(char	**s, char *value, int *i, t_env **env_lst);
void			hide_quotes(char	*s);
void			hide_wrapped_quotes(char *s, int *i, char c);
int				unclosed_double_qoutes(char *s, int i);

/*------------------- LIB ----------------------------*/
char			*join_strings(char *s1, char *s2);
//char			*get_env(char *s);
t_token			*parse_cmd(t_token_source *token_source, t_env **env_lst);
void			unflag_cmd_list(char **s);
void			unflag_pipe(char *s);
void			flag_pipe(char *source);
int				replace_pipe(char *source, int i, char c);

/******************** SYNTAX CHECKER *********************/
int				syntax_checker(char *cmd_line);
int				pipe_check(char *cmd_line, int *stx_error);
int				quotes_check(char *cmd_line, int *stx_error);
int				redirection_check(char *cmd_line, int *stx_error);
int				skip_spaces(char *cmd_line, int i);
int				end_of_cmd(char c);

/*****************	CMD LIST METHODS	*****************/
//void			delete_cmd_list(t_cmd_list	**cmd_list);

//****************	CMD METHODS	/******************/
int				is_cmd_exist(t_token *token);

/*****************	PARSER METHODS *****************/
t_token			*lexer(t_token_source *token_source);
void			quote_removal(t_token **tokens);
void			expander(t_token **token, t_env **env_lst);

/*****************	TOKEN_SOURCE METHODS *****************/
t_token_source	*init_token_source(char	*cmd_line);
char			goto_next_char(t_token_source *token_source);
char			get_next_char(t_token_source *token_source);
void			skip_space(t_token_source *token_source);
char			goto_last_char(t_token_source *token_source);

/***************** TOKEN METHODS *****************/
t_token			*create_token(char *value, int type);
t_token			*add_back_token(t_token **token, t_token	*new_token);
void			delete_token(t_token **token);
long			get_type_next_token(t_token *token);

/************ PARSING ERRORS *************/
void			throw_parssing_error(void);

/*TEMP*/
void			print_token(t_token *token);
// void	print_cmd_list(t_cmd_list *cmd_list);

#endif
