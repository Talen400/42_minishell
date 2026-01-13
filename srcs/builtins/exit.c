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
	if (str[i] == '+' || str[i] == '-')
		i++;
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
	int	is_valid;

	i = 0;
	exit_status = 0;
	is_valid = 1;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (args[1] && is_numeric(args[1]))
		exit_status = ft_atoi(args[1]);
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		is_valid = 0;
		exit_status = 1;
	}
	else if (args[1] && !is_numeric(args[1]))
	{
		exit_status = 2;
		ft_putendl_fd("exit: argument should be a number", STDERR_FILENO);
	}
	if (is_valid)
		data->is_running = 0;
	data->last_status = exit_status * 256;
	return (exit_status * 256);
}
