/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:27:26 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/08 13:31:04 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/minishell.h"

int	env(char **args, t_data *data)
{
	int	i;

	(void)args;
	i = 0;
	while (data->envvars[i])
	{
		ft_putendl_fd(data->envvars[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
