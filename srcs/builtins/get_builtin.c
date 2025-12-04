/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:25:45 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/04 13:53:04 by fbenini-         ###   ########.fr       */
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
	};

	i = 0;
	len = sizeof(commands) / sizeof(t_dict_builtin);
	while (i < len)
	{
		cmd_len = ft_strlen(commands[i].id);
		if (ft_strncmp(cmd, commands[i].id, cmd_len) == 0)
			return (commands[i].function);
		i++;
	}
	return (NULL);
}
