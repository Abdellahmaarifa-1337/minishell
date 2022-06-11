/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 01:34:52 by amaarifa          #+#    #+#             */
/*   Updated: 2022/06/11 11:14:23 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

void	expand_env_var(char	**s, char *value, int *i, t_env **env_lst)
{
	char	*temp;
	char	*expanded;
	int		start;

	start = *i;
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	if (start == *i)
		temp = ft_substr(value, start, *i - start + 1);
	else
		temp = ft_substr(value, start, *i - start);
	expanded = get_env(*env_lst, temp);
	if (!expanded)
		expanded = ft_strdup("");
	free(temp);
	if (value[*i] == '?')
	{
		free(expanded);
		expanded = ft_itoa(g_exit_status);
		*i += 1;
	}
	else if (start == *i)
		expanded = join_strings(ft_strdup("$"), expanded);
	hide_quotes(expanded);
	*s = join_strings(*s, expanded);
}

void	collect_none_var(char	*value, int *i, char **s)
{
	int		start;
	char	*temp;

	if (!(*s))
		*s = ft_strdup("");
	start = *i;
	while (value[*i] && !(value[*i] == '$' && value[*i + 1]
			&& (ft_isalpha(value[*i + 1]) || value[*i + 1] == '_')))
	{
		if (value[*i] == '\'' && !unclosed_double_qoutes(value, *i - 1))
		{	
			(*i)++;
			while (value[*i] && value[*i] != '\'')
				(*i)++;
		}
		(*i)++;
	}
	if (start == *i)
		temp = ft_substr(value, start, *i - start + 1);
	else
		temp = ft_substr(value, start, *i - start);
	*s = join_strings(*s, temp);
}

int	collect_var(char	*value, int *i, char **s, t_env **env_lst)
{
	(*i)++;
	if (!value[*i])
		*s = join_strings(*s, ft_strdup("$"));
	while (value[*i] && value[*i] == '$')
		(*i)++;
	if (!value[*i])
		return (0);
	expand_env_var(s, value, i, env_lst);
	return (1);
}

char	*expand_var(char *value, t_env **env_lst)
{
	int		i;
	char	*s;

	s = ft_strdup("");
	i = 0;
	while (value[i])
	{
		if (value[i] != '$' || (value[i + 1]
				&& !(ft_isalpha(value[i + 1]) || value[i + 1] == '_')))
		{
			collect_none_var(value, &i, &s);
			continue ;
		}
		else
		{
			if (!collect_var(value, &i, &s, env_lst))
				break ;
			continue ;
		}
	}
	return (s);
}

void	expander(t_token **token, t_env **env_lst)
{
	t_token	*temp;
	char	*str;

	temp = *token;
	while (temp)
	{
		temp->expand_heredoc = 0;
		if (temp->type != HERE_DOC)
		{
			str = temp->value;
			temp->value = expand_var(temp->value, env_lst);
			free(str);
		}
		else if (!ft_strchr(temp->value, '\'')
			&& !ft_strchr(temp->value, '\"'))
			temp->expand_heredoc = 1;
		hide_quotes(temp->value);
		temp = temp->next;
	}
}
