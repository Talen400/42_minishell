/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:12:14 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/26 04:22:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

// SIGINT (aka ctrl-C) helper functions

static void	handle_sigint(int signal)
{
	pid_t	child_pid;
	int		status;

	child_pid = waitpid(-1, &status, WNOHANG);
	(void)status;
	(void)signal;
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (child_pid == 0)
		return ;
	rl_replace_line("", 0);
	if (rl_line_buffer && rl_prompt)
	{
		ft_putstr_fd(rl_prompt, STDOUT_FILENO);
		if (rl_line_buffer)
			ft_putstr_fd(rl_line_buffer, STDOUT_FILENO);
	}
}

void	setup_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

void	restore_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
