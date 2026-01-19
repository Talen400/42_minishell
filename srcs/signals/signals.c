/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenini- <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:18:58 by fbenini-          #+#    #+#             */
/*   Updated: 2025/12/26 17:07:37 by fbenini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signals.h"

void	setup_signals(void)
{
	setup_sigint();
	setup_sigquit();
}

void	restore_signals(void)
{
	restore_sigquit();
	restore_sigint();
}
