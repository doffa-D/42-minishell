/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:20:41 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/06 00:03:02 by nouakhro         ###   ########.fr       */
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
	int HERDOC_OPTION;
	int APPEND;
	int ERROR_SYNTACSI;
	int ERROR_SYNTACSO;
	int ambiguous;
	int number_of_I;
	int number_of_O;

} t_files;

typedef struct each_command
{
	char **cmd;
	int fd[2];
	t_files *files;
} t_each_command;

typedef struct s_all
{
	char				**splite_pipe;
	char				*the_commande;
	char				**fix_cmd;
	char				**my_path;
	char				*tmp_cmd;
	char				*cmd;
	int 				if_rediraction;
	int					number_of_pipes;
	int 				exit_status;
	int					fils_descreprot;
	int					parccer;
	int					ambiguous;
	int					error_ambiguous;
	int 				status;
	int					check;
	t_each_command 		*each_cmd;
	t_list				*list;
}				t_all;

typedef struct s_var
{
	int index_i;
	int start;
	int index_j;
	int end;
} t_var;

void	exicut_commande(t_all *_struct, int i, int c_of_s, int *pipe_n);
int		check_rediractions(t_all *_struct, int c_of_s);
int		get_the_path(t_all *_struct, int c_of_s);
void	exit_the_program(t_all _struct);
void	free_all(t_all _struct);
void	exicut_echo(t_all *_struct, int c_of_s);
int		quote_check(char *cmd);
int		fix_arg(t_all *_struct);
char *my_getenv(t_list *head , char *var, int trim);
// void			rl_replace_line (const char *text, int clear_undo);
char	*ft_strjoin_v2(char const *s1, char const *s2);
// void check_leaks();
// void	handler(int sig);
int		cd_commade(t_all *_struct, int c_of_s);
void	fill_linked_list(char **dst, t_list **list);
int		mini_check_export(char *src,int x);
void	unset_command(t_all *_struct,int c_of_s);
void	env_command(t_list *list);
void	echo_command(t_all *_struct, int c_of_s);
void	export_command(t_all *_struct,int c_of_s);
int 	mini_search(char *str,char c);
int 	duplicate_check_export(t_list *list,char *dst);
int 	mini_search(char *str,char c);
void	add_node_back(char *str,t_list  **list);
void	string_dakche(t_list *list);
void	search_varible(char *cmd,t_list *list);
int		replace_varible(t_list *list,char *cmd);
int		mini_checker_export(t_list *list,char *cmd);
int 	check_varible_if_have(t_list *list,char *cmd);
void	print_export(t_list *list);
int 	builtins(t_all *_struct, int c_of_s);
void	pwd_command(void);
void	pipe_and_rederaction(int j, int c_of_s, t_all *_struct, int **pipe_n);
void	parccen(t_all *_struct);
int 	builtins(t_all *_struct, int c_of_s);
void	qouts(t_all *_struct, t_var *variables, int c_of_s);
int	check_rediractions_in_parent(t_all *_struct, int c_of_s);
#endif
