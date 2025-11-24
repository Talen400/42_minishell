/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_logical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:44:31 by fbenini-          #+#    #+#             */
/*   Updated: 2025/11/24 20:34:42 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_ast_node	*parse_logical(t_parser *parser)
{
	t_ast_node	*left;
	t_token		*token;
	t_ast_node	*logical;

	left = parse_pipeline(parser);
	if (!left)
		return (NULL);
	token = parser_current(parser);
	while (token && (token->type == TOKEN_AND || token->type == TOKEN_OR))
	{
		logical = create_node(NODE_LOGICAL);
		logical->u_data.logical.op = token->type;
		logical->u_data.logical.left = left;
		parser_advance(parser);
		logical->u_data.logical.right = parse_pipeline(parser);
		left = logical;
		token = parser_current(parser);
	}
	return (left);
}
