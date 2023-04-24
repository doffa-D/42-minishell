/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:20:41 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/24 16:56:25 by hdagdagu         ###   ########.fr       */
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
	char				**env;
	char				**export;
	char				**my_path;
	t_each_command 		*each_cmd;
	char				**splite_pipe;
	char				**fix_cmd;
	char				*the_commande;
	char				*cmd;
	int					number_of_pipes;
	char				*tmp_cmd;
	int 				exit_status;
	int					check;
	t_list				*list;
}				t_all;

typedef struct s_var
{
	int i;
	int c;
	int j;
} t_var;

void			exicut_commande(t_all *my_struct, int i, int c_of_s, int *pipe_n);
void			check_rediractions(t_all *my_struct, int c_of_s);
int			    get_the_path(t_all *my_struct, int c_of_s);
void			exit_the_program(t_all my_struct);
void			free_all(t_all my_struct);
void			exicut_echo(t_all *my_struct, int c_of_s);
int				quote_check(char *cmd);
int			fix_arg(t_all *my_struct);
char *my_getenv(t_list *head , char *var);
// void			rl_replace_line (const char *text, int clear_undo);
char	*ft_strjoin_v2(char const *s1, char const *s2);
// void check_leaks();
// void	handler(int sig);
int cd_commade(t_all *my_struct);
void    fill_linked_list(char **dst, t_list **list);
int	mini_check_export(char *src,int x);
void	unset_command(t_all *my_struct,int c_of_s);
void	env_command(t_list *list);
void	echo_command(t_all *my_struct, int c_of_s);
void	export_command(t_all *my_struct,int c_of_s);
int mini_search(char *str,char c);
int duplicate_check_export(t_list *list,char *dst);
int mini_search(char *str,char c);
void	add_node_back(char *str,t_list  **list);
void	string_dakche(t_list *list);
void	search_varible(char *cmd,t_list *list);
int	replace_varible(t_list *list,char *cmd);
int	mini_checker_export(t_list *list,char *cmd);
int check_varible_if_have(t_list *list,char *cmd);
void	print_export(t_list *list);
int builtins(t_all *my_struct, int c_of_s);
#endif
