/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automato_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:03:57 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/20 20:08:03 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

/*
 * TABLE DRIVE :
 *
 * ======================================
 *
 * states
 * 0: INIT
 * 1: D_QUOTE
 * 2: S_QUOTE
 * 3: VAR
 * 4: subshell
 * 5: State tempory to $VAR
 *
 *		 		LET	"	'	$	(	)	*	\0
 * state 0	=	0	1	2	0	0	0	0	0
 * state 1	=	1	0	1	3	1	1	1	0
 * state 2	=	2	2	0	2	2	2	2	0
 */

static int	(*get_table_expander(void))[NUM_TYPE_EXPANDER]
{
	static int	table[NUM_STATE_EXPANDER][NUM_TYPE_EXPANDER] = {
		{0, 1, 2, 0, 0, 0, 0, 0},
		{1, 0, 1, 1, 1, 1, 1, 0},
		{2, 2, 0, 2, 2, 2, 2, 0}
	};

	return (table);
}

static char	*get_env_expander(t_data *data, char *str)
{
	int		i;
	char	*res;
	size_t	len;

	i = 0;
	res = NULL;
	len = ft_strlen(str);
	while (data->envvars[i])
	{
		if (ft_strncmp(str, data->envvars[i], len) == 0
				&& data->envvars[i][len] == '=')
		{
			res = ft_strdup(data->envvars[i] + len + 1);
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

char	*append_char(char *str, char character)
{
	char	*ptr;

	ptr = ft_substr(&character, 0, 1);
	return (join_free(str, ptr));
}

void	check_state(t_automato_expander *aut)
{
	aut->prev_state = aut->state;
	aut->state = get_state_expander(aut, aut->word[aut->i]);
}

char	*handle_dollar(t_automato_expander *aut, t_data *data)
{
	int		start;
	int		len;
	char	*tmp;
	char	*result;

	aut->i++;
	start = aut->i;
	len = 0;
	while (aut->word[aut->i] && ((ft_isalnum(aut->word[aut->i])
				|| aut->word[aut->i] == '_')))
	{
		aut->i++;
		len++;
	}
	tmp = ft_substr(aut->word, start, len);
	ft_printf("tmp: %s %d \n", tmp, ft_strlen(tmp));
	if (*tmp == '\0')
		result = ft_strdup("$");
	else
		result = get_env_expander(data, tmp);
	ft_printf("result: %s \n", result);
	free(tmp);
	return (result);
}

/*
 * echo test'test'"test""$USER"'$USER'"$(echo $USER)" 
 */

int	is_expander(t_expandable_value *value, t_data *data)
{
	t_automato_expander	aut;

	ft_memset(&aut, 0, sizeof(t_automato_expander ));
	aut.word = value->raw;
	value->processed = ft_strdup("");
	aut.table = get_table_expander();
	ft_printf("\n maquina de estado da expansão! Raw: %s \n", value->raw);
	while (aut.word[aut.i])
	{
		check_state(&aut);
		ft_printf("[%d] prev: %d, state: %d, str: %c \n",
				aut.i, aut.prev_state, aut.state, aut.word[aut.i]);
		if ((aut.word[aut.i] == '\'' && (aut.state == 2 || aut.prev_state == 2))
				|| (aut.word[aut.i] == '\"' && (aut.state == 1 || aut.prev_state == 1)))
		{
			aut.i++;
			continue ;
		}
		if (aut.word[aut.i] == '$' && aut.state != 2)
		{
			aut.tmp = handle_dollar(&aut, data);
			value->processed = join_free(value->processed, aut.tmp);
			continue ;
		}
		value->processed = append_char(value->processed, aut.word[aut.i]);
		aut.i++;
	}
	if (aut.word[aut.i] == '\0')
		return (TRUE);
	return (FALSE);
}
