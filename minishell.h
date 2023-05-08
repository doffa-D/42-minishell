/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:20:41 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 23:51:18 by nouakhro         ###   ########.fr       */
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

#define IN_DCOTE 0
#define IN_COTE 1
#define VAR 3
#define WORD 4
#define OUTSIDE 5

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


t_all g_struct;

void	print_erro(void);
int		check_rediractions_in_parent(int c_of_s);
int		check_rediractions(int c_of_s);
int		check_export_error(char *cmd);
void	wait_and_close_all(int c_of_s, int *pid);
int		handle_export(char *cmd, int print, t_list *list);
void	export_command(int c_of_s);
void	last(t_list *list, char *cmd);
char	*variables_parceen(t_var *variables, char *whotout_expande, char *my_string);
int		len_2(char **str);
int		check_n(char *str);
void	env_command(t_list *list);
void	echo_command(int c_of_s);
char	*_get_env(t_list *head, int j, int trim, char *expande_variable);
char	*what_insied_herdoc(t_var *indes, char *buffer, char *herdoc);
char	*read_line_herdoc(int c_of_s, t_var *variables, char *herdoc);
void	comande_parcen_part(t_var *variables);
char	*variables_parceen_utils(char *whotout_expande, char *my_string, t_var *variables);
void	commande_and_args(t_var *variables);
void	splite_commande(t_var *variables);
int		remove_quotes_and_expande_variables_in_input(t_var *variables, int cas, int if_error);
int		inistialisation_input(t_var *variables, int c_of_s);
int		if_multiple_argemnt_in_rederaction_files(t_var *variables, int c_of_s, int if_error);
int		inistialisation_output(t_var *variables, int c_of_s);
int		change_quotes_and_pipe_and_rederaction(t_var *variables);
int		quote_and_dquote(t_var *variables);
char	*expande_variables_insied_herdoc(t_var *indes, char *buffer, char *herdoc);
int		parccen_part(t_var *variables);
int		partition_part(t_var *variables);
void	path_doase_not_exist(int c_of_s);
int		path_is_exist(int c_of_s, int j);
int		join_path_whit_commade(int c_of_s, int j, int *i);
void	pipe_is_exist_or_its_not_builtins(int c_of_s, int i);
int		other_string_beffor_end_of_line(t_var *variables, int cas);
void	pipe_and_rederaction_parceen(t_var *variables);
void	remove_quotes_and_expande_in_rederaction(t_var *variables, int c_of_s);
void	expande_variables_in_comande_parcen_part(t_var *variables);
void	parrcing_of_insied_herdoc(t_var *variables, int c_of_s);
void	initialisaion(t_var *variables, int c_of_s);
void	if_rediraction_is_existe(t_var *variables);
void	pwd_command(void);
int		commande_and_rederaction_parceen(t_var *variables, int c_of_s);
void	quotes(t_var *variables, int c_of_s);
void	expande_variables(t_var *var, int cas);
void	remove_single_quotes(t_var *variables, int c_of_s);
void	remove_double_quotes(t_var *variables, int c_of_s);
char	*fill_herdoc(char *buffer, t_var *indes, char *herdoc);
char	*my_getenv(t_list *head, char *var, int trim);
char	*split_variable_or_not(char *variable);
char	*exit_status(char *my_string, t_var *variables);
void	fill_linked_list(char **dst, t_list **list);
void	free_commande_whit_out_path(int i, int j);
void	error_in_commande(int c_of_s);
char	*_not_alphanum_after_dolar(char *whotout_expande, char *my_string, t_var *variables);
int		splite_argemnt(int i, int checker, char *splite_char);
void	_exit(int c_of_s);
void	error_is_exist(int c_of_s);
void	exicut_commande(int i, int c_of_s, int *pipe_n);
char	**new_env(t_list *list);
void	rediraction_calculate_input(t_var *variables, int c_of_s);
int		each_argemnt(int i, int j);
void	rediraction_calculate_output(t_var *variables, int c_of_s);
void	_path_comanmde(void);
void	syntax_error(t_var *variables);
char	*other_character_after_dolar(char *whotout_expande, char *my_string, t_var *variables);
char	*expande_all(char *whotout_expande, char *my_string, t_var *variables);
char	*is_alphabet_after_dolar(t_var *variables, char *whotout_expande, char *my_string, int end);
int		how_many_rederaction_input(t_var *variables, int c_of_s);
int		get_the_path(int c_of_s);
void	exit_the_program(t_all);
void	free_all(t_all);
void	exicut_echo(int c_of_s);
int		quote_check(char *cmd);
char	*my_getenv(t_list *head , char *var, int trim);
// void			rl_replace_line (const char *text, int clear_undo);
char	*ft_strjoin_v2(char const *s1, char const *s2);
// void check_leaks();
void	handler(int sig);
int		cd_commade(int c_of_s);
int		mini_check_export(char *src);
int		unset_command(int c_of_s);
int 	mini_search(char *str,char c);
int 	duplicate_check_export(t_list *list,char *dst);
void	add_node_back(char *str,t_list  **list);
void	string_dakche(t_list *list);
void	search_varible(char *cmd,t_list *list);
int		replace_varible(t_list *list,char *cmd);
int		mini_checker_export(t_list *list,char *cmd);
int 	check_varible_if_have(t_list *list,char *cmd);
void	print_export(t_list *list);
int 	builtins(int c_of_s);
void	pipe_and_rederaction(int j, int c_of_s, int **pipe_n);
void	parccen();
void	handler_herdoc(int sig);
void 	error_is_exist(int c_of_s);
int 	path_is_exist(int c_of_s, int j);
void 	handel_pipe_and_rederaction(int c_of_s);
void 	check_error_and_excute_comande(int c_of_s);
int		rederaction_and_builtins(int c_of_s);
void 	_path_comanmde();
int 	_parent_builtins(int c_of_s);
int 	after_parccing(int c_of_s);
int 	represent_between_each_argemnt(char	splite_char, int i, int *j);
int 	each_argemnt(int i, int j);
void 	exit_error_not_numeric(int c_of_s, int i);
void 	_exit(int c_of_s);
void 	some_builtins(int c_of_s);
void	 another_builtins(int c_of_s);
int 	some_builtins_in_parent(int c_of_s);
int		if_builtins_in_parent(int c_of_s);
int 	_is_builtins(int c_of_s);
int		if_builtins_in_chiled(int c_of_s);
int 	_only_cd(int pid, int c_of_s);
int 	_cd_whith_somthing(int c_of_s, int pid);
int 	_cd_whith_tilde(int c_of_s, int pid);
int 	_cd_whith_slash(int c_of_s, int pid);
int 	_cd(int c_of_s, int pid);
void 	free_commande_whit_out_path(int i, int j);
void	free_all_v2(int num);
int		exicut_bultins(int c_of_s, int output_buckup, int input_buckup);
void	return_fils_to_default(int output_buckup, int input_buckup);
int		how_many_rederaction_output(t_var *variables, int c_of_s);
void	remove_double_quotes_in_commande_parccing_part(t_var *variables);
void	remove_single_quotes_in_commande_parccing_part(t_var *variables);
int		quotes_comnde(t_var *variables);
int		partition_of_comande_and_rederaction(t_var *variables, int c_of_s);
t_list	*searcher(t_list *list, char *old);
t_list	*i_have(t_list *list, char *cmd);
int		idont_have(t_list *list, char *cmd);
int		fix_arg(void);
int		somting_in_readline(void);
int		builtins_in_parent(int c_of_s);
char* get_git_branch_name();
void free_parccing_part_after_error(void *malloc_error);
#endif
