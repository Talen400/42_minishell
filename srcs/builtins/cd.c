/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:32:08 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/04 16:56:07 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/data.h"
#include "../../includes/minishell.h"
#include <unistd.h>

int	cd(char **args, t_data *data)
{
	size_t	i;

	i = 0;
	(void)data;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	else if (i < 2)
	{
		ft_putendl_fd("cd: not enough arguments", STDERR_FILENO);
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		perror("cd: ");
		return (1);
	}
	return (0);
}
