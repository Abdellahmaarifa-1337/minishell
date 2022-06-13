/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:03:07 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/13 23:05:18 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*generate_unique_name(char *path, int id)
{
	char	*id_str;
	char	*name;

	id_str = ft_itoa(id);
	name = ft_strjoin(path, id_str);
	free(id_str);
	return (name);
}

char	*append_string(char *res, char *s)
{
	char	*tmp;
	char	*new_res;

	new_res = ft_strjoin(res, s);
	free(res);
	free(s);
	tmp = new_res;
	new_res = ft_strjoin(tmp, "\n");
	free(tmp);
	return (new_res);
}

void	hide_all_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			s[i] = -1;
		else if (s[i] == '\"')
			s[i] = -2;
		i++;
	}
}

void	return_all_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == -1)
			s[i] = '\'';
		else if (s[i] == -2)
			s[i] = '\"';
		i++;
	}
}

char	*expand_str(char *s, t_env	**env_lst)
{
	char	*tmp;

	hide_all_quotes(s);
	tmp = expand_var(s, env_lst);
	free(s);
	return_all_quotes(tmp);
	return (tmp);
}
