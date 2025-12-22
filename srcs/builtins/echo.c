/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:06:04 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/22 02:11:04 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

static void	run_echo(char **args, int skip)
{
	int	len;
	int	printed;
	int	i;

	len = 1;
	while (args[len])
		len++;
	len--;
	i = 1 + skip;
	printed = 0;
	while (args[i])
	{
		if (i <= len && printed > 0)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(args[i++], STDOUT_FILENO);
		printed++;
	}
}

int	echo(char **args, t_data *data)
{
	int	i;
	int	line_break;

	(void)data;
	i = 0;
	while (args[i])
		i++;
	if (i < 2)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		return (SUCESS);
	}
	line_break = 1;
	i = 1;
	if (ft_strncmp(args[i++], "-n\0", 3) == 0)
		line_break = 0;
	run_echo(args, !line_break);
	if (line_break)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCESS);
}
