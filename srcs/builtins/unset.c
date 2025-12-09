/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:04:03 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/08 16:06:40 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/minishell.h"

int	unset(char **args, t_data *data)
{
	size_t	i;

	i = 1;
	while (args[i])
	{
		delete_env(data, args[i]);
		i++;
	}
	return (0);
}
