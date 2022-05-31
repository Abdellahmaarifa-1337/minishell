/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:15:00 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 21:06:52 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
* 
* The main function for parssing the cmd line, and fill the cmd_list struct.
* The fucntion generate a list of tokens [cmd].
* Each node (Token) represent single command in a pipe line.
*
*/

int	get_number_cmd(char **cmd_lines)
{
	int	i;

	i = 0;
	while (cmd_lines[i])
		i++;
	return (i);
}

void	parser(t_cmd_list	*cmd_list)
{
	int		i;
	char	**cmd_lines;

	flag_pipe(cmd_list->source);
	cmd_lines = ft_split(cmd_list->source, '|');
	unflag_cmd_list(cmd_lines);
	cmd_list->tokens = (t_token **)malloc(sizeof(t_token *)
			* (get_number_cmd(cmd_lines) + 1));
	i = 0;
	while (cmd_lines[i])
	{
		(cmd_list->tokens)[i] = parse_cmd(init_token_source(
					ft_strtrim(cmd_lines[i], " ")));
		free(cmd_lines[i]);
		i++;
	}
	(cmd_list->tokens)[i] = NULL;
	free(cmd_lines);
	return ;
}
