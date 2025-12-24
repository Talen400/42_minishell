/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:05:14 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/12 16:45:19 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>
#define BLUE "\e[0;104m"
#define GREEN "\e[1;32m"
#define RESET "\e[0m"
#define GRAY "\033[1m"

static char	**init_envvars(char **envvars)
{
	size_t	i;
	char	**res;

	i = 0;
	while (envvars[i])
		i++;
	res = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envvars[i])
	{
		res[i] = ft_strdup(envvars[i]);
		i++;
	}
	return (res);
}

void	clear_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->envvars[i])
	{
		free(data->envvars[i]);
		i++;
	}
	free(data->envvars);
	free(data->user);
}

char	*get_prompt(char *user)
{
	char	*res;
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	res = ft_strjoin(user, RESET"@"BLUE"minishell"RESET GRAY" ");
	tmp = ft_strjoin(res, pwd);
	free(pwd);
	free(res);
	res = tmp;
	tmp = ft_strjoin(res, RESET"\n > ");
	free(res);
	res = tmp;
	return (res);
}

int	init_data(t_data *data, char **envvars)
{
	int		i;

	data->envvars = init_envvars(envvars);
	data->user = NULL;
	data->is_running = 1;
	data->exit_status = 0;
	i = 0;
	while (envvars[i])
	{
		if (ft_strncmp(envvars[i], "USER=", 5) == 0)
			data->user = envvars[i] + 5;
		i++;
	}
	if (!data->user)
		data->user = "marvin";
	data->user = ft_strjoin(GREEN, data->user);
	return (0);
}
