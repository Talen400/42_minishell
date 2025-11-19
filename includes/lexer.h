/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:06:46 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/19 18:24:42 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# define NUM_STATE 14
# define NUM_TYPES 12

typedef enum e_char_type
{
	WHITE_SPACE = 0,
	WORD = 1,
	PIPE = 2,
	REDIRECT_INPUT = 3,
	REDIRECT_OUTPUT = 4,
	OR = 5,
	AND = 6,
	OPEN_P = 7,
	CLOSE_P = 8,
	QUOTE = 9,
	DOUBLE_QUOTE = 10,
	_NULL = 11
}	t_char_type;

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

typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
}	t_token;

// table_driven.c
t_char_type	get_char_type(char c);
int			get_state(t_automato *aut, char character);

// automato.c
int			state_final(t_automato *aut, char *str);
int			state_is_final(int state);
int			automato(char *str);

#endif
