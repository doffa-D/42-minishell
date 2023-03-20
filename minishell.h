/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:20:41 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/20 19:42:50 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>

typedef struct s_all
{
	size_t		linght_path;
	char		**my_path;
	char		**my_all_path;
	char		*my_curent_path;
	char		**my_command;
	char		**fix_cmd;
	char		*read_all;
	char		*test;
	const char	*cmd;
	int			command_len;
	int			i;
	int 		dollar;
}				t_all;

void			exicut_commande(t_all my_struct, int i);
void			check_rediractions(t_all my_struct);
int			    get_the_path(t_all my_struct);
void			exit_the_program(t_all my_struct);
void			free_all(t_all my_struct);
void			exicut_echo(t_all *my_struct);
int				quote_check(char *cmd);
void			fix_arg(t_all *my_struct);
void			rl_replace_line (const char *text, int clear_undo);

#endif
