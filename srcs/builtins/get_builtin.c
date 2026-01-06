/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:25:45 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/12 14:41:31 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/minishell.h"

t_builtin_cmd	get_builtin(char *cmd)
{
	size_t					i;
	size_t					len;
	size_t					cmd_len;
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
	len = sizeof(commands) / sizeof(t_dict_builtin);
	cmd_len = ft_strlen(cmd);
	if (cmd_len == 0)
		return (NULL);
	while (i < len)
	{
		if (ft_strncmp(cmd, commands[i].id, cmd_len) == 0)
			return (commands[i].function);
		i++;
	}
	return (NULL);
}
