/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:20:41 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/09 16:08:06 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H
#include "libft/libft.h"
#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_all
{

	size_t  linght_path;
	char **my_path;
	char **my_all_path;
	char *my_curent_path;
	char **my_command;
	char *read_all;
	const char *cmd;
	int command_len;
}               t_all;

void exicut_commande(t_all my_struct, int i);
void check_rediractions(t_all my_struct);
void get_the_path(t_all my_struct);
void exit_the_program(t_all my_struct);
void free_all(t_all my_struct);

#endif

