/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:36:10 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/03 16:44:59 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

char	*handle_fail(t_data *data)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	data->is_running = 0;
	return (NULL);
}

char	*ft_readline(t_data *data)
{
	char	*line;
	char	*prompt;
	size_t	len;

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
	prompt = get_prompt(data->user);
	line = readline(prompt);
	free(prompt);
	if (!line)
		return (handle_fail(data));
	add_history(line);
	return (line);
}
