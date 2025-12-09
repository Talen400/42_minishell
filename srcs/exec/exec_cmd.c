/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:00:35 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/09 14:55:54 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include <unistd.h>

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
	return (path + 5);
}

static void	free_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
}

static char	*get_path_of_cmd(char *cmd, t_data *data)
{
	char	**paths;
	char	*res;
	char	*formatted_path;
	int		i;

	paths = ft_split(get_path(data), ':');
	i = 0;
	res = NULL;
	while (paths[i])
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
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	**convert_expandable(t_expandable_value **values)
{
	int		i;
	char	**res;

	i = 0;
	while (values[i])
		i++;
	res = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (values[i])
	{
		if (values[i]->processed)
			res[i] = ft_strdup(values[i]->processed);
		else
			res[i] = ft_strdup(values[i]->raw);
		i++;
	}
	return (res);
}

int	exec_cmd(t_ast_node *node, t_data *data)
{
	char		*path;
	t_cmd_node	cmd;
	char		**args;
	int			res;

	if (node->type != NODE_CMD)
		return (1);
	cmd = node->u_data.cmd;
	args = convert_expandable(cmd.args);
	path = get_path_of_cmd(args[0], data);
	if (!path)
	{
		ft_putstr_fd("minishell: Command not found: ", STDERR_FILENO);
		ft_putendl_fd(args[0], STDERR_FILENO);
		free_splitted(args);
		return (127);
	}
	res = execve(path, args, data->envvars);
	free(path);
	free_splitted(args);
	return (res);
}
