/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:26:15 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/15 17:45:28 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "data.h"
# include "minishell.h"
# include "parser.h"

int		handle_paren(char *cmd, t_data *data);
int		exec_ast(t_ast_node *root, t_data *data, int status);

int		exec_cmd(t_ast_node *node, t_data *data);
char	**convert_expandable(t_expandable_value **values);

void	free_splitted(char **splitted);
char	*get_path_of_cmd(char *cmd, t_data *data);
int		exec_from_builtin(t_builtin_cmd builtin, char **args, t_data *data);

int		exec_pipe(t_ast_node *node, t_data *data);

typedef struct s_pipe_args
{
	t_pipe_node	pipe_node;
	int			fd[2];
	int			fd_in;
	pid_t		pid;
	int			status;
	int			is_last;
	int			i;
	pid_t		last_pid;
}	t_pipe_args;

typedef struct s_redirect_args
{
	int	og_stdout;
	int	og_stdin;
}	t_redirect_args;

void	child_process(t_ast_node *node, t_data *data, t_pipe_args *args);
void	father_process(t_pipe_args *args);

int		handle_redirects(t_ast_node *node, t_redirect_args *args);
void	restore_std(t_redirect_args *args);

int		handle_heredoc(const char *eof, t_data *data);

#endif
