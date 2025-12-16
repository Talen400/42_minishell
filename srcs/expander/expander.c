/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:55:11 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/16 18:44:35 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/expander.h"

static char	*get_env(t_data *data, char *str)
{
	int		i;
	char	*res;
	size_t	len;

	i = 0;
	res = NULL;
	len = ft_strlen(str);
	while (data->envvars[i])
	{
		if (ft_strncmp(str + 1, data->envvars[i], len - 1) == 0)
		{
			res = ft_strdup(data->envvars[i] + len);
			return (res);
		}
		i++;
	}
	res = ft_strdup("");
	return (res);
}

char	*join_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}
/*
 *
 *
 * Here is experimental automato expanser
 *
 *
 */

# define NUM_TYPE_EXPANSER 8
# define NUM_STATE_EXPANSER 6

typedef struct s_automato_expanser
{
	int	i;
	int	state;
	int	prev_state;
	int	str_len;
	int	(*table)[NUM_TYPE_EXPANSER];

}	t_automato_expanser;

enum e_char_type_expanser
{
	LETTER_EXPANSER,
	D_QUOTE_EXPANSER, // "
	S_QUOTE_EXPANSER, // '
	SIMPLE_VAR_EXPANSER, // $
	OPEN_PAR_EXPANSER,
	CLOSE_PAR_EXPANSER,
	WILDCARD_EXPANSER, // *
	DOLLAR_EXPANSER // $( )
};

/*
 * TABLE DRIVE :
 *
 * ======================================
 *
 * states (complet tokens)
 * 0: S_QUOTE
 * 1: D_QUOTE
 * 2: END S_QUOTE
 * 3: END D_QUOTE
 * 4: EXPANSER
 * 5: END EXPANSER
 *
 *		 		LET	"	'	$	(	)	*	\0
 * state 0	=	0	1	2	2	2	2	2	0
 * state 1	=	0	1	0	0	0	0	0	0
 * state 2	=	0	0	3	3	3	3	0	0
 * state 3	=	0	0	0	0	0	0	0	0
 * state 4	=	4	4	4	4	4	4	4	0
 * state 5	=	5	5	5	5	5	5	5	0
 */

static int	(*get_table_expanser(void))[NUM_TYPE_EXPANSER]
{
	static int	table[NUM_STATE_EXPANSER][NUM_TYPE_EXPANSER] = {
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	};

	return (table);
}

int	get_char_type(char c)
{
	if (c == '"')
		return (D_QUOTE_EXPANSER);
	if (c == '\'')
		return (S_QUOTE_EXPANSER);
	if (c == '$')
		return (DOLLAR_EXPANSER);
	if (c == '(')
		return (OPEN_PAR_EXPANSER);
	if (c == ')')
		return (CLOSE_PAR_EXPANSER);
	if (c == '*')
		return (WILDCARD_EXPANSER);
	return (LETTER_EXPANSER);
}

int	ft_is_expanser(t_expandable_value *value, t_data *data)
{
	char	*str;
	char	*ptr;
	int		j;
	int		i;
	int		is_expand;
	int		(*table)[NUM_TYPE_EXPANSER];
	
	str = value->raw;
	is_expand = FALSE;
	j = 0;
	value->processed = ft_strdup("");
	table = get_table_expanser();
	while (str[j])
	{
		ft_printf("str[%d]: %c \n", j, str[j]);
		i = 0;
		if (str[j] == '"')
		{
			while (str[i] != '"')
				i++;
			ptr = ft_substr(str, j, i + 1);
			value->processed = join_free(value->processed, ptr);
			j += i;
			is_expand = TRUE;
		}
		else if (str[j] == '\'')
			is_expand = TRUE;
		else if (str[j] == '$')
			is_expand = TRUE;
		else if (str[j] == '*')
			is_expand = TRUE;
		else if (str[j] && str[j + 1] == '$' && str[1] == '(')
			is_expand = TRUE;
		j++;
	}
	if (is_expand == TRUE)
	{
		ft_printf("Yes! %s \n", value->raw);
	}
	(void ) data;
	return (FALSE);
}

void	expand_var(t_expandable_value *value, t_data *data)
{
	ft_printf("type: %d, content: %s \n", value->type, value->raw);
	ft_is_expanser(value, data);
	(void ) get_env;
	/*
	if (ft_is_expanser(value, data))
		return ;
	else if (value->type == SIMPLE_VAR)
		value->processed = get_env(data, value->raw);
	else if (value->type == LITERAL)
		value->processed = ft_strdup(value->raw);
	else if (value->type == WILDCARD)
		value->processed = wildcard(value->raw);
	else if (value->type == QUOTED)
		value->processed = quote(value->raw);
	*/
}

void	expand_cmd(t_ast_node *node, t_data *data)
{
	int	i;

	if (node->type != NODE_CMD)
		return ;
	i = 0;
	while (node->u_data.cmd.args[i])
	{
		expand_var(node->u_data.cmd.args[i], data);
		i++;
	}
	i = 0;
	while (node->u_data.cmd.redirects[i])
	{
		expand_var(node->u_data.cmd.redirects[i]->target, data);
		i++;
	}
	expand_var(node->u_data.cmd.cmd, data);
}

void	expand_ast(t_ast_node *root, t_data *data)
{
	if (!root)
		return ;
	if (root->type == NODE_LOGICAL)
	{
		expand_ast(root->u_data.logical.left, data);
		expand_ast(root->u_data.logical.right, data);
	}
	if (root->type == NODE_CMD)
		expand_cmd(root, data);
}
