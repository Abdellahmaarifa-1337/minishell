/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaarifa <amaarifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 01:34:52 by amaarifa          #+#    #+#             */
/*   Updated: 2022/05/29 23:02:35 by amaarifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser.h"

void	expand_env_var(char	**s, char *value, int *i)
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
	expanded = get_env(temp);
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

	start = *i;
	while (value[*i] && value[*i] != '$')
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

int	collect_var(char	*value, int *i, char **s)
{
	(*i)++;
	if (!value[*i])
		*s = join_strings(*s, ft_strdup("$"));
	while (value[*i] && value[*i] == '$')
		(*i)++;
	if (!value[*i])
		return (0);
	expand_env_var(s, value, i);
	return (1);
}

char	*expand_var(char *value)
{
	int		i;
	char	*s;

	s = ft_strdup("");
	i = 0;
	while (value[i])
	{
		if (value[i] != '$')
		{
			collect_none_var(value, &i, &s);
			continue ;
		}
		else
		{
			if (!collect_var(value, &i, &s))
				break ;
			continue ;
		}
	}
	return (s);
}

void	expander(t_token **token)
{
	t_token	*temp;
	char	*str;

	temp = *token;
	while (temp)
	{
		if (temp->type != HERE_DOC)
		{
			str = temp->value;
			temp->value = expand_var(temp->value);
			free(str);
		}
		hide_quotes(temp->value);
		temp = temp->next;
	}
}