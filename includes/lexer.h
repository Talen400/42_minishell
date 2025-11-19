/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:06:46 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/18 17:59:37 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

#define NUM_STATE 7
#define NUM_TYPES 18

enum e_char_type
{
	WHITE_SPACE,
	LETTER,
	DIGIT,
	OPERATOR,
	QUOTE,
	PIPE,
	REDIRECT,
	OTHER,
};

typedef struct s_token
{
	int		type;
	char	*data;
}	t_token;

typedef struct s_automato
{
	int			i;
	int			state;
	int			token_type;
	int			str_len;
	int			lexeme_len;
	char		*lexeme;
	int			(*table)[NUM_TYPES];
}	t_automato;

typedef struct s_node_token
{
	t_token	*token;
	struct s_node_token	*next;
}	t_node_token;

#endif
