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

static t_ast_node	*handle_seq(t_ast_node **nodes, size_t count, size_t cap)
{
	t_ast_node	*node;

	node = create_node(NODE_SEQ);
	node->u_data.sequence.commands = nodes;
	node->u_data.sequence.count = count;
	node->u_data.pipe.capacity = cap;
	return (node);
}

static t_ast_node	*handle_pipe(t_ast_node **nodes, size_t count, size_t cap)
{
	t_ast_node	*node;

	node = create_node(NODE_PIPE);
	node->u_data.pipe.commands = nodes;
	node->u_data.pipe.count = count;
	node->u_data.pipe.capacity = cap;
	return (node);
}

static t_ast_node	**insert_nodes(t_parser *parser, size_t *node_cap, t_parser_rule *rule,
								size_t *node_count, t_ast_node *left, t_parser_function parse_function)
{
	t_ast_node	**nodes;
	t_ast_node	*next;
	t_token		*token;
	size_t		count;

	count = *node_count;
	nodes = malloc(sizeof(t_ast_node *) * 8);
	nodes[count++] = left;
	token = parser_current(parser);
	while (token && token->type == rule->token_type)
	{
		parser_advance(parser);
		next = parse_function(parser);
		if (!next)
			break ;
		if (count >= *node_cap)
		{
			*node_cap *= 2;
			ft_realloc(nodes, *node_cap);
		}
		nodes[count++] = next;
		token = parser_current(parser);
	}
	*node_count = count;
	return (nodes);
}

t_ast_node	*parse_generic(t_parser *parser, t_parser_rule *rule,
						t_parser_function parse_function)
{
	t_ast_node	*left;
	t_token		*token;
	size_t		node_cap;
	size_t		node_count;
	t_ast_node	**nodes;

	left = parse_function(parser);
	token = parser_current(parser);
	if (!token || token->type != rule->token_type)
		return (left);
	node_cap = 8;
	node_count = 0;
	nodes = insert_nodes(parser, &node_cap, rule, &node_count, left, parse_function);
	if (node_count == 1)
	{
		free(nodes);
		return (left);
	}
	if (rule->node_type == NODE_SEQ)
		return (handle_seq(nodes, node_count, node_cap));
	if (rule->node_type == NODE_PIPE)
		return (handle_pipe(nodes, node_count, node_cap));
	free(nodes);
	return (left);
}
