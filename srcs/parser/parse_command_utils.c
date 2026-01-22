/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:35:32 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/22 13:35:44 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	handle_redirect_failure(t_redirect_value *redir_node)
{
	free(redir_node->type);
	free(redir_node->target);
	free(redir_node);
	return (FAILURE);
}
