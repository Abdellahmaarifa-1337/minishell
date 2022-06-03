/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkabissi <mkabissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:33:47 by mkabissi          #+#    #+#             */
/*   Updated: 2022/06/03 16:47:35 by mkabissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../types.h"

/********** CONVERT TOKEN INTO 3D ARRAY **********/

char	**join_string(char **cmd, char *value, int len)
{
	char	**p;
	int		i;

	p = (char **)malloc(sizeof(char *) * (len + 2));
	if (!p)
		perror("malloc error");
	i = 0;
	while (i < len)
	{
		p[i] = ft_strdup(cmd[i]);
		i++;
	}
	p[i] = ft_strdup(value);
	p[++i] = NULL;

printf("%s ", p[0]);
	return (p);
}

char	***token_to_3d(t_cmd_list *list)
{
	t_token	*temp;
	char	***cmd;
	char	**ptr;
	int		i;
	int		k;
	int		len;

	while (list->tokens[list->n_cmd])
		list->n_cmd++;
	cmd = (char ***)malloc(sizeof(char **) * (list->n_cmd + 1));
	if (!cmd)
		perror("malloc error");
	k = 0;
	while (list->tokens[k])
	{
		i = 0;
		len = 0;
		temp = list->tokens[k];
		while (temp != NULL)
		{
			if (temp->type == WORD)
			{
			printf("(%d) ", i);
			printf (">>> %s ", temp->value);
				if (i > 0)
				{
					ptr = join_string(cmd[i], temp->value, len);
					free(cmd[i]);
					cmd[i] = ptr;
				}
				else
					cmd[i] = join_string(NULL, temp->value, len);
				// if (len < 2)
				// exit(0);
				i++;
				len++;
			}
			temp = temp->next;
		}
		printf("\n");
		k++;
	}
	cmd[k] = NULL;
	return (cmd);
}


/********** PRINT THE 3D ARRAY OF PARAMETERS **********/

void	print_3dparms(char ***parms)
{
	int	i;
	int	j;

	i = -1;
	while (parms[++i])
	{
		j = -1;
		printf("------- Command %d -------\n", i + 1);
		while (parms[i][++j])
			printf("%s ", parms[i][j]);
		printf("\n--------------------------\n");
	}
}
