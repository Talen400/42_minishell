/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:40:08 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/05 16:57:51 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/data.h"
#include "../../includes/minishell.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

void	update_env(t_data *data, char *key, char *new_value)
{
	size_t	i;
	char	*id;
	size_t	id_len;
	char	*res;

	i = 0;
	id = ft_strjoin(key, "=");
	while (data->envvars[i])
	{
		id_len = ft_strlen(data->envvars[i]);
		if (ft_strncmp(data->envvars[i], id, id_len) == 0)
		{
			res = join_and_free(id, new_value);
			free(data->envvars[i]);
			data->envvars[i] = res;
			break ;
		}
		i++;
	}
	free(new_value);
}
