/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:25:45 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/15 17:06:48 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/minishell.h"

t_builtin_cmd	get_builtin(char *cmd)
{
	size_t					i;
	size_t					len;
	static t_dict_builtin	commands[] = {
	{"pwd", pwd},
	{"echo", echo},
	{"cd", cd},
	{"env", env},
	{"unset", unset},
	{"export", ft_export},
	{"exit", ft_exit}
	};

	i = 0;
	if (!cmd)
		return (NULL);
	len = sizeof(commands) / sizeof(t_dict_builtin);
	while (i < len)
	{
		if (ft_strcmp(cmd, commands[i].id) == 0)
			return (commands[i].function);
		i++;
	}
	return (NULL);
}
