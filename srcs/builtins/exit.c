/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:19:22 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/11 13:31:03 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_data *data)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	data->is_running = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		exit_status = 2;
	}
	if (args[1] && is_numeric(args[1]))
		exit_status = ft_atoi(args[1]);
	else if (args[1] && !is_numeric(args[1]))
	{
		exit_status = 2;
		ft_putendl_fd("exit: argument should be a number", STDERR_FILENO);
	}
	data->exit_status = exit_status;
	return (exit_status);
}
