/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:20:41 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/18 23:11:34 by nouakhro         ###   ########.fr       */
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

typedef struct s_files
{
	char *files;
	int INPUT;
	int OUTPUT;
	int HERDOC;
	int APPEND;
	int ERROR_SYNTACSI;
	int ERROR_SYNTACSO;
	int number_of_I;
	int number_of_O;

} t_files;

typedef struct each_command
{
	char **cmd;
	t_files *files;

} t_each_command;

typedef struct s_all
{
	int 				status;
	int 				if_rediraction;
	char				**my_path;
	t_each_command 		*each_cmd;
	char				**splite_pipe;
	char				**fix_cmd;
	char				*the_commande;
	char				*cmd;
	int					number_of_pipes;
	char				*tmp_cmd;
}				t_all;

typedef struct s_var
{
	int i;
	int c;
	int j;
} t_var;

void			exicut_commande(t_all *my_struct, int i, int c_of_s);
void			check_rediractions(t_all *my_struct, int c_of_s);
int			    get_the_path(t_all *my_struct, int c_of_s);
void			exit_the_program(t_all my_struct);
void			free_all(t_all my_struct);
void			exicut_echo(t_all *my_struct);
int				quote_check(char *cmd);
int			fix_arg(t_all *my_struct);
void			rl_replace_line (const char *text, int clear_undo);
char	*ft_strjoin_v2(char const *s1, char const *s2);
void check_leaks();

#endif
