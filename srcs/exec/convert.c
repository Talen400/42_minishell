/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:58:56 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/09 17:27:14 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	count_wildcards(t_expandable_value *value)
{
	int		i;
	char	**splitted;

	if (value->type != WILDCARD && !value->processed)
		return (1);
	i = 0;
	splitted = ft_split(value->processed, ' ');
	while (splitted[i])
		i++;
	free_splitted(splitted);
	return (i);
}

static void	create_arg(t_expandable_value *value, char **args, int *j)
{
	char	**splitted;
	int		split_idx;

	split_idx = 0;
	if (value->type == WILDCARD)
	{
		splitted = ft_split(value->processed, ' ');
		while (splitted[split_idx])
		{
			args[*j] = splitted[split_idx];
			split_idx++;
			*j += 1;
		}
		free(splitted);
		return ;
	}
	if (value->processed)
		args[*j] = ft_strdup(value->processed);
	else
		args[*j] = ft_strdup(value->raw);
	*j += 1;
}

char	**convert_expandable(t_expandable_value **values)
{
	int		i;
	int		j;
	int		count;
	char	**res;

	i = 0;
	count = 0;
	while (values[i])
	{
		if (values[i]->type == WILDCARD)
			count += count_wildcards(values[i]);
		i++;
		count++;
	}
	res = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (values[i])
	{
		create_arg(values[i], res, &j);
		i++;
	}
	return (res);
}
