/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:40:08 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/08 18:07:13 by fbenini-         ###   ########.fr       */
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

static void	create_new_var(t_data *data, char *id, char *new_value)
{
	size_t	size;
	char	**new;
	size_t	i;

	size = 0;
	while (data->envvars[size])
		size++;
	new = ft_calloc(size + 2, sizeof(char *));
	i = 0;
	while (data->envvars[i])
	{
		new[i] = data->envvars[i];
		i++;
	}
	new[i++] = join_and_free(id, new_value);
	free(data->envvars);
	data->envvars = new;
}

void	update_env(t_data *data, char *key, char *new_value)
{
	size_t	i;
	char	*id;
	size_t	id_len;
	char	*res;

	i = 0;
	id = ft_strjoin(key, "=");
	res = NULL;
	while (data->envvars[i])
	{
		id_len = ft_strlen(id);
		if (ft_strncmp(data->envvars[i], id, id_len) == 0)
		{
			res = join_and_free(id, new_value);
			free(data->envvars[i]);
			data->envvars[i] = res;
			break ;
		}
		i++;
	}
	if (!res)
		create_new_var(data, id, new_value);
}

void	pop_from_env(t_data *data, size_t pos)
{
	size_t	i;
	char	**new;
	size_t	j;

	i = 0;
	while (data->envvars[i])
		i++;
	new = ft_calloc(i, sizeof(char *));
	i = 0;
	j = 0;
	while (data->envvars[i])
	{
		if (i != pos)
		{
			new[j] = data->envvars[i];
			j++;
		}
		else
			free(data->envvars[i]);
		i++;
	}
	free(data->envvars);
	data->envvars = new;
}

void	delete_env(t_data *data, char *key)
{
	char	*id;
	size_t	i;
	size_t	id_len;

	id = ft_strjoin(key, "=");
	i = 0;
	while (data->envvars[i])
	{
		id_len = ft_strlen(id);
		if (ft_strncmp(data->envvars[i], id, id_len) == 0)
			pop_from_env(data, i);
		i++;
	}
	free(id);
}
