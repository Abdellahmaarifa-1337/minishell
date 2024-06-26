/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:23:30 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/14 20:34:24 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <unistd.h>
# include "./src/libft/libft.h"
# include "fcntl.h"
# include "signal.h"
# include <termios.h>

# define EMPTY_TOKEN -1
# define AMBIGUOUS_REDIRECT -2
# define HERE_DOC 0				/*	<<		*/
# define IN_REDERCTIONT 1		/*	< 		*/
# define OUT_TRUNC 2			/*	>		*/
# define APPEND 3				/*	>>		*/
# define WORD 4					/*	ex: ls	*/

/* EXIT STATUS */
int	g_exit_status;

/* ENV */
typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* TOKEN */
typedef struct s_token {
	char			*value;	
	int				type;
	int				expand_heredoc;
	struct s_token	*next;
}	t_token;

/* TOKEN SOURCE */

typedef struct s_token_source {
	char	*source;
	char	current_char;
	long	current_position;
	long	size;
}	t_token_source;

/* MUILPILE PIP COMMANDS REPRESNTATION STRUCUER */

typedef struct s_cmd_list {
	char	*source;
	char	*cmd_line;
	int		exit;
	t_token	**tokens;
	t_env	**env;
}	t_cmd_list;

typedef struct s_data {
	int			n;
	int			n_cmd;
	int			status;
	t_env		**env_lst;
	t_cmd_list	*cmd_lst;
}	t_data;

typedef struct s_syntax_dt {
	int				stx_error;
	int				end;
	int				error;
	int				first_lap;
	unsigned int	first_address;
}	t_syntax_dt;

void	rl_replace_line(char *string, int i);

#endif

/*
	int ***pip;
	pip[3] = {{0,1}, ...};

	while (i < 3)
	{
		in = get_in(token); // -1
		out = get_out  // -1
		cmd = get_cmd(token);
		
		i++;
	}
*/
