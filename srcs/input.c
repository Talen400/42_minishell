/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:36:10 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/12 16:36:35 by fbenini-         ###   ########.fr       */
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
	char	*prompt;
	size_t	len;

	// mode pipes to terminal to terminal
	if (!isatty(STDIN_FILENO))
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
		}
		return (line);
	}
	// mode interative with terminal
	prompt = get_prompt(data->user);
	line = readline(prompt);
	free(prompt);
	add_history(line);
	return (line);
}
