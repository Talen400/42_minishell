/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:05:14 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/19 15:32:40 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>
#define BLUE "\e[0;104m"
#define GREEN "\e[1;32m"
#define RESET "\e[0m"
#define GRAY "\033[1m"

static char	*handle_shlvl(char *og_value)
{
	int		value;
	char	*value_str;
	char	*res;

	value = ft_atoi(og_value + 6);
	value += 1;
	value_str = ft_itoa(value);
	res = ft_strjoin("SHLVL=", value_str);
	free(value_str);
	return (res);
}

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
		if (ft_strncmp(envvars[i], "SHLVL=", 6) == 0)
		{
			res[i] = handle_shlvl(envvars[i]);
			i++;
			continue ;
		}
		res[i] = ft_strdup(envvars[i]);
		i++;
	}
	return (res);
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

static pid_t	get_pid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
		exit(0);
	return (pid);
}

int	init_data(t_data *data, char **envvars)
{
	int		i;

	data->pid = get_pid();
	data->envvars = init_envvars(envvars);
	data->user = NULL;
	data->is_running = 1;
	data->last_status = 0;
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
