/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:06:04 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/08 12:33:45 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

static void	run_echo(char **args, void (*f)(char *s, int fd))
{
	int	len;
	int	i;

	len = 1;
	while (args[len])
		len++;
	len--;
	i = 2;
	while (args[i])
	{
		f(args[i++], STDOUT_FILENO);
		if (f == ft_putstr_fd && i <= len)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	echo(char **args, t_data *data)
{
	int	i;
	int	line_break;

	i = 1;
	(void)data;
	while (args[i])
		i++;
	if (i < 2)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		return (SUCESS);
	}
	line_break = 1;
	i = 1;
	if (ft_strncmp(args[i++], "-n", 2) == 0)
		line_break = 0;
	else
		ft_putendl_fd(args[i - 1], STDOUT_FILENO);
	if (line_break)
		run_echo(args, ft_putendl_fd);
	else
		run_echo(args, ft_putstr_fd);
	return (SUCESS);
}
