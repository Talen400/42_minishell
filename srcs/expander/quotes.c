/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:10:37 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/09 21:20:01 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

char	*quote(char *raw)
{
	char	*res;
	int		len;

	len = ft_strlen(raw);
	res = NULL;
	if (raw[0] == '"' || raw[0] == '\'')
		res = ft_substr(raw, 1, len - 2);
	return (res);
}
