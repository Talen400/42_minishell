/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:07:43 by tlavared          #+#    #+#             */
/*   Updated: 2026/01/14 19:24:08 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/checker.h"

int	is_word(int type)
{
	return (type == TOKEN_WORD
		|| type == TOKEN_SQUOTE
		|| type == TOKEN_DQUOTE
		|| type == TOKEN_EXPANSER);
}

int	is_logical_or_pipe(int type)
{
	return (type == TOKEN_PIPE
		|| type == TOKEN_AND
		|| type == TOKEN_OR);
}

int	is_redirect(int type)
{
	return (type == TOKEN_REDIR_IN
		|| type == TOKEN_APPEND
		|| type == TOKEN_REDIR_OUT
		|| type == TOKEN_HEREDOC);
}
