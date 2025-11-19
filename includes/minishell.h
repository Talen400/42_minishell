/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:31:03 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/19 20:41:59 by tlavared         ###   ########.fr       */
/*   Updated: 2025/11/18 15:55:22 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include "../libft/libft.h"
# include "data.h"
# define SUCESS 0
# define FAILURE 1
# define TRUE 1
# define FALSE 0

int	read_input(t_data *data);
#endif
