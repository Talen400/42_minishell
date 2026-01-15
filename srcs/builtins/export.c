/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:45:32 by fbenini-          #+#    #+#             */
/*   Updated: 2026/01/15 17:17:00 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/minishell.h"

static int	is_valid_id(char *str)
{
	int	i;

	i = 0;
	if (!str[i] || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

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

/*
 * Modifiquei esse export_aux e coloquei para ele procurar
 * pelo sinal de '=' dentro dele mesmo
 * :>
 */

static void	export_aux(t_data *data, char *arg)
{
	char	*key;
	char	*value;

	key = copy_key(arg);
	value = ft_strchr(arg, '=');
	if (value)
		update_env(data, key, value + 1);
	else
		update_env(data, key, "");
	free(key);
}

int	ft_export(char **args, t_data *data)
{
	size_t	i;

	if (!args[0])
		return (0);
	if (!args[1])
	{
		ft_putendl_fd("export: not enough arguments", 2);
		return (1);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_id(args[i]))
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			data->exit_status = 1;
		}
		else if (ft_strchr(args[i], '='))
			export_aux(data, args[i]);
		i++;
	}
	return (data->exit_status * 256);
}
