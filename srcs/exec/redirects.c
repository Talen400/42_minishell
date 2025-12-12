	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   redirects.c                                        :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: fbenini- <fbenini-@student.42sp.org.br>    +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2025/12/11 17:02:40 by fbenini-          #+#    #+#             */
	/*   Updated: 2025/12/11 17:02:40 by fbenini-         ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parser.h"
#include <unistd.h>

t_redirect_value	*find_redirect(t_cmd_node *cmd, int type)
{
	int					i;
	t_redirect_value	*res;

	res = NULL;
	i = 0;
	while (cmd->redirects[i])
	{
		if (cmd->redirects[i]->og_fd == type)
			res = cmd->redirects[i];
		i++;
	}
	return (res);
}
