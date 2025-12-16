/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:55:11 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/16 15:50:19 by tlavared         ###   ########.fr       */
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

int	ft_is_expanser(t_expandable_value *value, t_data *data)
{
	char	*str;
	int		is_expand;

	str = value->raw;
	is_expand = FALSE;
	while (*str)
	{
		if (*str == '"')
			is_expand = TRUE;
		else if (*str == '\'')
			is_expand = TRUE;
		else if (*str == '$')
			is_expand = TRUE;
		else if (*str == '*')
			is_expand = TRUE;
		else if (str[1] && str[0] == '$' && str[1] == '(')
			is_expand = TRUE;
		str++;
	}
	if (is_expand == TRUE)
	{
		ft_printf("Yes! %s \n", value->raw);
		return (TRUE);
	}
	(void ) data;
	return (FALSE);
}

void	expand_var(t_expandable_value *value, t_data *data)
{
	ft_printf("type: %d, content: %s \n", value->type, value->raw);
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
