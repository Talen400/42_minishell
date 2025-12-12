/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:36:10 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/12 14:55:06 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

int	read_input(t_data *data)
{
	char	*line;

	(void)data;
	line = readline(data->prompt);
	if (!line)
		return (1);
	add_history(line);
	rl_redisplay();
	while (line)
	{
		free(line);
		line = readline(data->prompt);
		if (!line)
			return (1);
		add_history(line);
		rl_redisplay();
	}
	free(line);
	return (0);
}

char	*ft_readline(t_data *data)
{
	char	*line;

	line = readline(data->prompt);
	add_history(line);
	return (line);
}
