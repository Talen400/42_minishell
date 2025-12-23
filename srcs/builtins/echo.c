/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:06:04 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/23 11:30:08 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

int	echo(char **args, t_data *data)
{
	int	i;
	int	line_break;

	(void)data;
	i = 1;
	line_break = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		line_break = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (line_break)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCESS);
}
