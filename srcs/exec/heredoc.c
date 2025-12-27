/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 22:45:16 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/26 22:52:33 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static void	write_loop(const char *eof, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

int	handle_heredoc(const char *eof)
{
	int			write_fd;
	int			read_fd;
	const char	*tmp_file;

	tmp_file = "/tmp/heredoc_minishell";
	write_fd = open(tmp_file, O_CREAT | O_WRONLY | O_EXCL, 0600);
	if (write_fd < 0)
	{
		perror("minishell");
		return (-1);
	}
	write_loop(eof, write_fd);
	read_fd = open(tmp_file, O_RDONLY);
	if (read_fd < 0)
	{
		perror("minishell");
		unlink(tmp_file);
		return (-1);
	}
	unlink(tmp_file);
	return (read_fd);
}
