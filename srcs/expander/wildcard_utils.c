/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:59:14 by tlavared          #+#    #+#             */
/*   Updated: 2026/01/15 17:05:20 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

void	free_split(char **split)
{
	int	i;

	if (split)
	{
		i = -1;
		while (split[++i])
			free(split[i]);
		free(split);
	}
}
