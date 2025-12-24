/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:31:03 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/21 21:51:14 by tlavared         ###   ########.fr       */
/*   Updated: 2025/11/18 15:55:22 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "data.h"
# include "builtins.h"
# define SUCESS 0
# define FAILURE 1
# define TRUE 1
# define FALSE 0

int		minishell(char *line, t_data *data);
char	*ft_readline(t_data *data);
char	*get_prompt(char *user);

#endif
