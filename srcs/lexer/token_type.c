/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:08:01 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/24 19:09:29 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	get_type_token(int state, char *lexeme)
{
	if (state == 1)
		return (TOKEN_WORD);
	if (state == 2)
	{
		if (lexeme[0] == '|')
			return (TOKEN_PIPE);
		if (lexeme[0] == '<')
			return (TOKEN_REDIR_IN);
		if (lexeme[0] == '>')
			return (TOKEN_REDIR_OUT);
		if (lexeme[0] == '(')
			return (TOKEN_OPEN_PAR);
		if (lexeme[0] == ')')
			return (TOKEN_CLOSE_PAR);
	}
	if (state == 3)
	{
		if (lexeme[0] == '|' && lexeme[1] == '|')
			return (TOKEN_OR);
		if (lexeme[0] == '&' && lexeme[1] == '&')
			return (TOKEN_AND);
		if (lexeme[0] == '<' && lexeme[1] == '<')
			return (TOKEN_HEREDOC);
		if (lexeme[0] == '>' && lexeme[1] == '>')
			return (TOKEN_APPEND);
	}
	if (state == 6)
		return (TOKEN_SQUOTE);
	if (state == 7)
		return (TOKEN_DQUOTE);
	if (state == 8 || state == 9)
		return (TOKEN_EXPANSER);
	return (-1);
}
