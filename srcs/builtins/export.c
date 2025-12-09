/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:45:32 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/08 18:11:49 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/minishell.h"

static char	*copy_key(char *arg)
{
	size_t	i;
	char	*res;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	res = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		res[i] = arg[i];
		i++;
	}
	return (res);
}

static void	export_aux(t_data *data, char *arg)
{
	char	*key;
	char	*new_value;

	new_value = ft_strchr(arg, '=');
	key = copy_key(arg);
	if (!new_value)
		update_env(data, key, "");
	else
		update_env(data, key, new_value + 1);
	free(key);
}

int	ft_export(char **args, t_data *data)
{
	size_t	i;

	if (!args[1])
	{
		ft_putendl_fd("export: not enough arguments", 2);
		return (1);
	}
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			export_aux(data, args[i]);
		i++;
	}
	return (0);
}
