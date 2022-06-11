/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:57:10 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/11 21:00:56 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	dup_stdin_stdout(int *int_out, int *stdin_saved, int *stdout_saved)
{
	if (int_out[0] > -1)
	{
		*stdin_saved = dup(STDIN_FILENO);
		dup2(int_out[0], STDIN_FILENO);
	}
	if (int_out[1] > -1)
	{
		*stdout_saved = dup(STDOUT_FILENO);
		dup2(int_out[1], STDOUT_FILENO);
	}
}

void	close_open_files(int *int_out, int *stdin_saved, int *stdout_saved)
{
	if (int_out[0] > -1)
		close(int_out[0]);
	if (int_out[1] > -1)
		close(int_out[1]);
	if (*stdin_saved > -1)
		dup2(*stdin_saved, STDIN_FILENO);
	if (*stdout_saved > -1)
		dup2(*stdout_saved, STDOUT_FILENO);
}

void	exec_single_cmd(t_cmd_list *cmd_lst, t_env **env_lst)
{
	char	**args;
	int		stdin_saved;
	int		stdout_saved;
	int		int_out[2];

	stdin_saved = -1;
	stdout_saved = -1;
	args = get_args(cmd_lst->tokens);
	if (resolve_path(args, cmd_lst->env, 0) == 0)
		return ;
	get_in_out_file((cmd_lst->tokens)[0], int_out, 0);
	if (int_out[0] == -1 || int_out[1] == -1)
		return ;
	dup_stdin_stdout(int_out, &stdin_saved, &stdout_saved);
	if (!args)
		exit(1);
	execute_command(args, env_lst, cmd_lst, 1);
	close_open_files(int_out, &stdin_saved, &stdout_saved);
	if (args)
	{
		ft_free((void **)args, get_size_of_arr((void **)args));
		free(args);
	}
	return ;
}
