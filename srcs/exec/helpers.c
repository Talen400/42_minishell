/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:50:24 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/18 16:26:41 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static char	*get_path(t_data *data)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (data->envvars[i])
	{
		if (ft_strncmp(data->envvars[i], "PATH=", 5) == 0)
			path = data->envvars[i];
		i++;
	}
	if (!path)
		return (NULL);
	return (path + 5);
}

void	free_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted && splitted[i])
		free(splitted[i++]);
	free(splitted);
}

static char	**split_paths(t_data *data)
{
	char	*path;
	char	**splitted;

	path = get_path(data);
	if (!path)
		return (NULL);
	splitted = ft_split(path, ':');
	return (splitted);
}

char	*get_path_of_cmd(char *cmd, t_data *data)
{
	char	**paths;
	char	*res;
	char	*formatted_path;
	int		i;

	paths = split_paths(data);
	i = 0;
	res = NULL;
	while (paths && paths[i])
	{
		formatted_path = ft_strjoin(paths[i++], "/");
		res = ft_strjoin(formatted_path, cmd);
		free(formatted_path);
		if (access(res, F_OK) == 0)
		{
			free_splitted(paths);
			return (res);
		}
		else
			free(res);
	}
	free_splitted(paths);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

int	exec_from_builtin(t_builtin_cmd builtin, char **args, t_data *data)
{
	int	status;

	if (!builtin)
		return (-1);
	status = builtin(args, data);
	free_splitted(args);
	return (status);
}
