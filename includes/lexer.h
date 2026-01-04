/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:06:46 by tlavared          #+#    #+#             */
/*   Updated: 2026/01/04 19:10:51 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# define NUM_STATE 10
# define NUM_TYPES 14

enum e_char_type
{
	WSPACE,
	LETTER,
	PIPE,
	AND,
	LESS,
	GREATER,
	OPEN_PAR,
	CLOSE_PAR,
	S_QUOTE,
	D_QUOTE,
	DOLLAR,
	LBRACE,
	RBRACE,
	NUL
};

enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_REDIR_IN,
	TOKEN_HEREDOC,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_OPEN_PAR,
	TOKEN_CLOSE_PAR,
	TOKEN_SQUOTE,
	TOKEN_DQUOTE,
	TOKEN_EXPANSER,
	TOKEN_SUB_CMD
};

typedef struct s_automato
{
	int			i;
	int			state;
	int			prev_state;
	int			token_type;
	int			str_len;
	int			lexeme_len;
	char		*lexeme;
	int			(*table)[NUM_TYPES];
}	t_automato;

typedef struct s_token
{
	int				type;
	char			*lexeme;
	struct s_token	*next;
}	t_token;

// table_driven.c
int			get_char_type(char c);
int			get_state(t_automato *aut, char character);

// automato.c
int			state_is_final(int state);
int			state_final(t_automato *aut, char *str, t_token **tokens);
int			automato(char *str, t_token **tokens);

// token.c
t_token		*create_node_token(char *lexeme, int type);
void		add_front_token(t_token **list, char *lexeme, int type);
void		token_clear_list(t_token **list);

// token_type.c
int			get_type_token(int state, char *lexeme);

// utils_lexer.c

void		handle_subshell_token(t_automato *aut, char *str);
int			update_state(t_automato *aut, char c);
void		handle_state_final(t_automato *aut, char *str, t_token **tokens);
void		handle_subshell(t_automato *aut, char *str);

// debug.c
void		print_tokens(t_token *tokens);

// check_syntax.c
int			check_syntax(t_token *tokens);

#endif
