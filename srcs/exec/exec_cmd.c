/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:00:35 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/09 18:27:03 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../includes/exec.h"
#include <time.h>

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

void	free_splitted(char **splitted)
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

int	exec_from_path(char **args, t_data *data)
{
	char	*path;
	int		status;
	pid_t	pid;

	status = 0;
	path = get_path_of_cmd(args[0], data);
	if (!path)
	{
		ft_putstr_fd("minishell: Command not found: ", STDERR_FILENO);
		ft_putendl_fd(args[0], STDERR_FILENO);
		free_splitted(args);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		status = execve(path, args, data->envvars);
		free(path);
		free_splitted(args);
		exit(status);;
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork failed");
	free(path);
	free_splitted(args);
	return (status);
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

int	exec_cmd(t_ast_node *node, t_data *data)
{
	t_cmd_node		cmd;
	char			**args;
	t_builtin_cmd	builtin;

	if (node->type != NODE_CMD)
		return (1);
	cmd = node->u_data.cmd;
	args = convert_expandable(cmd.args);
	builtin = get_builtin(args[0]);
	if (builtin)
		return (exec_from_builtin(builtin, args, data));
	return (exec_from_path(args, data));
}
