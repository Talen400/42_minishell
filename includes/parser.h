/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:46:49 by fbenini-          #+#    #+#             */
/*   Updated: 2025/11/24 12:07:47 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "minishell.h"

typedef struct s_ast_node	t_ast_node;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_LOGICAL,
	NODE_SEQ,
}							t_node_type;

typedef struct s_redirect_node
{
	char					*type;
	char					*target;
}							t_redirect_node;

typedef struct s_cmd_node
{
	char					*cmd;
	char					**args;
	size_t					argc;
	t_redirect_node			**redirects;
	size_t					redirect_count;
}							t_cmd_node;

typedef struct s_pipe_node
{
	t_ast_node				**commands;
	size_t					count;
	size_t					capacity;
}							t_pipe_node;

typedef struct s_logical_node
{
	enum e_char_type		op;
	t_ast_node				*left;
	t_ast_node				*right;
}							t_logical_node;

typedef struct s_sequence_node
{
	t_cmd_node				**commands;
	size_t					count;
	size_t					capacity;
}							t_sequence_node;

struct						s_ast_node
{
	t_node_type				type;
	union
	{
		t_cmd_node			cmd;
		t_pipe_node			pipe;
		t_logical_node		logical;
		t_sequence_node		sequence;
	} u_data;
};

typedef struct s_parser
{
	size_t					pos;
	size_t					count;
	t_token					**tokens;
}							t_parser;

typedef t_ast_node			*(*t_parser_function)(t_parser *);
// parser/init.c
t_ast_node					*create_node(t_node_type type);
t_parser					*init_parser(char *str);

#endif
