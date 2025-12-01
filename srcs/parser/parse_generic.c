/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_generic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:03:08 by fbenini-          #+#    #+#             */
/*   Updated: 2025/11/24 20:40:38 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_ast_node	*handle_pipe(t_ast_node **nodes, size_t count, size_t cap)
{
	t_ast_node	*node;

	node = create_node(NODE_PIPE);
	node->u_data.pipe.commands = nodes;
	node->u_data.pipe.count = count;
	node->u_data.pipe.capacity = cap;
	return (node);
}

static t_ast_node	**insert_nodes(t_node_insert *args)
{
	t_ast_node	*next;
	t_token		*token;
	size_t		count;

	count = args->node_count;
	args->nodes = ft_calloc(8 + 1, sizeof(t_ast_node *));
	args->nodes[count++] = args->left;
	token = parser_current(args->parser);
	while (token && token->type == args->rule->token_type)
	{
		parser_advance(args->parser);
		next = args->parse_function(args->parser);
		if (!next)
			break ;
		if (count >= args->node_cap)
		{
			args->node_cap *= 2;
			ft_realloc(args->nodes, args->node_cap + 1);
		}
		args->nodes[count++] = next;
		token = parser_current(args->parser);
	}
	args->nodes[count] = NULL;
	args->node_count = count;
	return (args->nodes);
}

t_ast_node	*parse_generic(t_parser *parser, t_parser_rule *rule,
						t_parser_function parse_function)
{
	t_token			*token;
	t_node_insert	insert_args;

	insert_args.left = parse_function(parser);
	insert_args.parser = parser;
	insert_args.parse_function = parse_function;
	insert_args.rule = rule;
	if (!insert_args.left)
		return (NULL);
	token = parser_current(parser);
	if (!token || token->type != rule->token_type)
		return (insert_args.left);
	insert_args.node_cap = 8;
	insert_args.node_count = 0;
	insert_args.nodes = insert_nodes(&insert_args);
	if (insert_args.node_count == 1)
	{
		free(insert_args.nodes);
		return (insert_args.left);
	}
	if (rule->node_type == NODE_PIPE)
		return (handle_pipe(insert_args.nodes,
				insert_args.node_count, insert_args.node_cap));
	free(insert_args.nodes);
	return (insert_args.left);
}
