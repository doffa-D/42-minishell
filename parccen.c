/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/01 19:28:47 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define IN_DCOTE 0
#define IN_COTE 1
#define VAR 3
#define WORD 4
#define OUTSIDE 5

char	*ft_strjoin_v2(char const *s1, char const *s2)
{
	char	*b;
	int		i;
	int		j;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	b = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!b)
		return (b);
	j = 0;
	while (s1[i])
	{
		b[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		b[i] = s2[j];
		i++;
		j++;
	}
	b[i] = 0;
	free((char *)s1);
	free((char *)s2);
	return (b);
}

int	quote_and_dqout(t_all *my_struct, t_var *variables)
{
	if ((my_struct->fix_cmd[variables->i][variables->j] == 34)
		&& my_struct->status != IN_COTE)
	{
		if (my_struct->fix_cmd[variables->i][variables->j] == 34
			&& my_struct->status == IN_DCOTE)
			my_struct->status = OUTSIDE;
		else
			my_struct->status = IN_DCOTE;
	}
	if ((my_struct->fix_cmd[variables->i][variables->j] == 39)
		&& my_struct->status != IN_DCOTE)
	{
		if (my_struct->fix_cmd[variables->i][variables->j] == 39
			&& my_struct->status == IN_COTE)
			my_struct->status = OUTSIDE;
		else
			my_struct->status = IN_COTE;
	}
	return (variables->c);
}

void	pipe_and_rederaction_parceen(t_all *my_struct, t_var *variables)
{
	if (my_struct->fix_cmd[variables->i][variables->j] == '|'
		&& my_struct->status == OUTSIDE)
	{
		my_struct->fix_cmd[variables->i][variables->j] = 4;
		my_struct->number_of_pipes++;
	}
	if (my_struct->fix_cmd[variables->i][variables->j] == '>'
		&& my_struct->status == OUTSIDE)
	{
		my_struct->fix_cmd[variables->i][variables->j] = 2;
		my_struct->if_rediraction = 1;
	}
	if (my_struct->fix_cmd[variables->i][variables->j] == '<'
		&& my_struct->status == OUTSIDE)
	{
		my_struct->fix_cmd[variables->i][variables->j] = 5;
		my_struct->if_rediraction = 1;
	}
}

char *my_getenv(t_list *head , char *var, int trim)
{
	int j = 0;
	(void)var;
	int i = 0;
	char *expande_variable = ft_calloc(1, 1);
	// char *variable = 0;
	// (void)trim;
	while (head)
	{
		if(*(char *)head->content == var[0])
		{
			j = 0;
			while(((char *)head->content)[j] == var[j] || \
			((char *)head->content)[j] == '=')
			{
				if(((char *)head->content)[j] == '=' && !var[j])
				{
					expande_variable = ft_substr(head->content, j + 1, ft_strlen(head->content + (j + 1)));
					i = 0;
					if(trim == 1)
					{
						// variable = expande_variable;
						// expande_variable = ft_strtrim(expande_variable, " ");
						// free(variable);
						while (expande_variable[i])
						{
							if(expande_variable[i] == ' ')
								expande_variable[i] = 3;
							i++;
						}
					}
					return(expande_variable);
				}
				j++;
			}
		}
		head = head->next;
	}
	return(expande_variable);
}

char *variables_parceen(t_all *my_struct, t_var *variables,char *whotout_expande, char *my_string)
{
	int		var;
	char	*variable;

	var = variables->j + 1;
	while (whotout_expande[var]
		&& (ft_isalpha(whotout_expande[var]) || ft_isdigit(whotout_expande[var])))
		var++;
	if (my_struct->status == IN_DCOTE || my_struct->status == OUTSIDE)
	{
		if(ft_isdigit(whotout_expande[variables->j + 1]) \
		&& whotout_expande[variables->j + 1] != '_')
		{
			variables->j++;
			variable = ft_substr(whotout_expande, \
			variables->j + 1, (var - (variables->j + 1)));
			my_string = ft_strjoin_v2(my_string, variable);
			variables->j = var - 1;
		}
		else if(ft_isalpha(whotout_expande[variables->j + 1]) \
		|| whotout_expande[variables->j + 1] == '_')
		{
			variable = ft_substr(whotout_expande, variables->j + 1,
					(var - (variables->j + 1)));
			if(my_struct->status == IN_DCOTE)
				variable = my_getenv(my_struct->list,variable, 0);
			else
				variable = my_getenv(my_struct->list,variable, 1);
			if (variable)
				my_string = ft_strjoin(my_string, variable);
			variables->j = var - 1;
		}
	}
	if (my_struct->status == IN_COTE)
	{
		variable = ft_substr(whotout_expande, variables->j,
				(var - variables->j));
		my_string = ft_strjoin_v2(my_string, \
			variable);
		variables->j = var - 1;
	}
	return my_string;
}


char *variables_parceen_rederaction(char *whotout_expande, char *my_string ,t_all *my_struct, t_var *variables)
{
	if (ft_isalnum(whotout_expande[variables->j + 1]))
	{
		if (whotout_expande[variables->j + 1])
		{
			variables->c++;
			my_string = variables_parceen(my_struct, variables, whotout_expande ,my_string);
			variables->c = variables->j;
		}
	}
	else
	{
		if(whotout_expande[variables->j + 1] == '?')
		{
			if(my_struct->status != IN_COTE)
			{
				variables->j++;
				my_string = ft_strjoin(my_string,ft_itoa(my_struct->exit_status));
				variables->c = variables->j;
			}
		}
		else if((whotout_expande[variables->j + 1] == 34 || whotout_expande[variables->j + 1] == 39) && my_struct->status == OUTSIDE)
			variables->c = variables->j;
		else if(!ft_isalnum(whotout_expande[variables->j + 1]) && whotout_expande[variables->j + 1] != '$')
		{
			variables->j++;
			variables->c = variables->j;
		}
		else 
		{
			variables->j++;
			variables->c = variables->j - 1;
		}
	}
	return my_string;
}


char *variables_parceen_utils(char *whotout_expande, char *my_string ,t_all *my_struct, t_var *variables)
{
	if (ft_isalnum(whotout_expande[variables->j + 1]))
	{
		if (whotout_expande[variables->j + 1])
		{
			variables->c++;
			my_string = variables_parceen(my_struct, variables, whotout_expande ,my_string);
			variables->c = variables->j;
		}
	}
	else
	{
		if(whotout_expande[variables->j + 1] == '?')
		{
			if(my_struct->status != IN_COTE)
			{
				variables->j++;
				my_string = ft_strjoin(my_string,ft_itoa(my_struct->exit_status));
				variables->c = variables->j;
			}
			else
				variables->c = variables->j - 1;
		}
		else if(my_struct->status != OUTSIDE && (whotout_expande[variables->j + 1] == 34 || whotout_expande[variables->j + 1] == 39))
			variables->c = variables->j - 1;
		else if(!ft_isalnum(whotout_expande[variables->j + 1]) && whotout_expande[variables->j + 1] != '$' \
		&& whotout_expande[variables->j + 1] != 34 && whotout_expande[variables->j + 1] != 39)
		{
			variables->j++;
			variables->c = variables->j;
		}
		else if(whotout_expande[variables->j + 1] == '$')
		{
			variables->j++;
			variables->c = variables->j - 1;
		}
	}
	return my_string;
}

int	parccen_part(t_all *my_struct, t_var *variables, char *splite)
{
	while (my_struct->fix_cmd[variables->i])
	{
		variables->j = 0;
		my_struct->status = OUTSIDE;
		while (my_struct->fix_cmd[variables->i][variables->j])
		{
			quote_and_dqout(my_struct, variables);
			pipe_and_rederaction_parceen(my_struct, variables);
			if((my_struct->fix_cmd[variables->i][variables->j] \
			== 4 && !my_struct->fix_cmd[variables->i + 1]) || \
			(my_struct->fix_cmd[variables->i][variables->j] == 4 && variables->i == 0))
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				return 258;
			}
			variables->j++;
		}
		if(my_struct->status != OUTSIDE)
		{
			ft_putstr_fd("minishell: unexpected EOF while looking for matching\n", 2);
			return -1;
		}
		my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, my_struct->fix_cmd[variables->i]);
		if(my_struct->fix_cmd[variables->i + 1])
			my_struct->the_commande = ft_strjoin(my_struct->the_commande, splite);
		my_struct->fix_cmd[variables->i] = 0;
		variables->i++;
	}
	return 1;
}


void	initialisaion(t_all *my_struct, t_var *variables, int c_of_s)
{
	my_struct->each_cmd[variables->i].files[c_of_s].OUTPUT = 0;
	my_struct->each_cmd[variables->i].files[c_of_s].APPEND = 0;
	my_struct->each_cmd[variables->i].files[c_of_s].number_of_O = 0;
	my_struct->each_cmd[variables->i].files[c_of_s].number_of_I = 0;
	my_struct->each_cmd[variables->i].files[c_of_s].INPUT = 0;
	my_struct->each_cmd[variables->i].files[c_of_s].HERDOC = 0;
	my_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSO = 0;
	my_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSI = 0;
	my_struct->each_cmd[variables->i].files[c_of_s].HERDOC_OPTION = 0;
}

int 	inistialisation_input(t_all *my_struct, t_var *variables, int c_of_s,
		int var)
{
	char **str;
	int checher = 0;
	if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_I > 2)
		checher = 1;
	if(my_struct->each_cmd[variables->i].files[c_of_s].number_of_O \
	&& my_struct->each_cmd[variables->i].files[c_of_s].number_of_I)
		checher = 1;
	if(!my_struct->tmp_cmd[variables->j])
		checher = 1;
	if(checher == 1)
	{
		checher = fork();
		if(checher == 0)
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			exit(1);
		}
		wait(&checher);
		return -1;
	}
	variables->c = variables->j - 1;
	my_struct->each_cmd[variables->i].files[c_of_s].files = ft_calloc(1, 1);
	if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_I == 2)
		my_struct->each_cmd[variables->i].files[c_of_s].HERDOC = 1;
	qouts(my_struct, variables, var , c_of_s);
	str = ft_split(my_struct->each_cmd[variables->i].files[c_of_s].files, 3);
	checher = 0;
	if(str[checher])
	{
		free(my_struct->each_cmd[variables->i].files[c_of_s].files);
		my_struct->each_cmd[variables->i].files[c_of_s].files = 0;
	}
	while (str[checher])
	{
		my_struct->each_cmd[variables->i].files[c_of_s].files = str[checher];
		checher++;
	}
	if(checher > 1)
	{
		checher = fork();
		if(checher == 0)
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			exit(1);
		}
		wait(&checher);
		my_struct->exit_status = checher >> 8;
		return -2;
	}
	// printf("%s\n",my_struct->each_cmd[variables->i].files[c_of_s].files);
	if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_I == 1)
		my_struct->each_cmd[variables->i].files[c_of_s].INPUT = 1;
	else if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_I == 2)
	{
		// if(my_struct->fils_descreprot)
		// 	close(my_struct->fils_descreprot);
		int fd_by_pipe[2];
		char *buffer = 0;
		char *buffer_tmp = 0;
		char *herdoc = ft_strdup("");
		int i = 0;
		int c = 0;
		pipe(fd_by_pipe);
		while (1)
		{
			buffer = readline("> ");
			if(!buffer)
				break;
			if (!ft_strncmp(buffer, my_struct->each_cmd[variables->i].files[c_of_s].files,
					ft_strlen(buffer) + 1))
				break ;
			if(ft_strchr(buffer, '$') && my_struct->each_cmd[c_of_s].files[c_of_s].HERDOC_OPTION == 0)
			{
				i = 0;
				c = 0;
				while (buffer[i])
				{
					if((buffer[i] == '$' \
						&& buffer[i + 1] \
						&& buffer[i + 1] != ' '))
					{
						herdoc = ft_strjoin_v2(herdoc, ft_substr(buffer, c, i - c));
						i++;
						if(buffer[i] == '?')
						{
							herdoc = ft_strjoin_v2(herdoc, ft_itoa(my_struct->exit_status));
							i++;
							c = i;
						}
						else
						{
							c = i;
							while (ft_isalnum(buffer[i]))
								i++;
							buffer_tmp = ft_substr(buffer, c, i - c);
							// printf("%s\n",buffer_tmp);
							herdoc = ft_strjoin_v2(herdoc, my_getenv(my_struct->list, buffer_tmp,0));
							// exit(0);
							free(buffer_tmp);
							c = i;
						}
						i--;
					}
					if(!buffer[i])
						break;
					i++;
				}
				herdoc = ft_strjoin_v2(herdoc, ft_substr(buffer, c, i - c));
			}
			else
				herdoc = ft_strjoin(herdoc, buffer);
			herdoc = ft_strjoin(herdoc, "\n");
		}
		ft_putstr_fd(herdoc, fd_by_pipe[1]);
		close(fd_by_pipe[1]);
		free(herdoc);
		my_struct->fils_descreprot = fd_by_pipe[0];
	}
	if(ft_strchr(my_struct->each_cmd[variables->i].files[c_of_s].files, 6) && \
	ft_strlen(my_struct->each_cmd[variables->i].files[c_of_s].files) == 1)
		my_struct->each_cmd[variables->i].files[c_of_s].files = ft_strdup("");
	return 0;
}

int		inistialisation_output(t_all *my_struct, t_var *variables, int c_of_s,
		int var)
{
	char **str;
	int checher = 0;
	if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O > 2)
		checher = 1;
	if(my_struct->each_cmd[variables->i].files[c_of_s].number_of_O \
	&& my_struct->each_cmd[variables->i].files[c_of_s].number_of_I)
		checher = 1;
	if(!my_struct->tmp_cmd[variables->j])
		checher = 1;
	if(checher == 1)
	{
		checher = fork();
		if(checher == 0)
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			exit(1);
		}
		wait(&checher);
		return -1;
	}
	if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O == 2)
		my_struct->each_cmd[variables->i].files[c_of_s].APPEND = 1;
	else if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O == 1)
		my_struct->each_cmd[variables->i].files[c_of_s].OUTPUT = 1;
	variables->c = variables->j - 1;
	my_struct->each_cmd[variables->i].files[c_of_s].files = ft_calloc(1, 1);
	qouts(my_struct, variables, var , c_of_s);
	str = ft_split(my_struct->each_cmd[variables->i].files[c_of_s].files, 3);
	checher = 0;
	if(str[checher])
	{
		free(my_struct->each_cmd[variables->i].files[c_of_s].files);
		my_struct->each_cmd[variables->i].files[c_of_s].files = 0;
	}
	while (str[checher])
	{
		my_struct->each_cmd[variables->i].files[c_of_s].files = str[checher];
		checher++;
	}
	if(checher > 1)
	{
		checher = fork();
		if(checher == 0)
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			exit(1);
		}
		wait(&checher);
		my_struct->exit_status = checher >> 8;
		return -2;
	}
	if(ft_strchr(my_struct->each_cmd[variables->i].files[c_of_s].files, 6) && \
	ft_strlen(my_struct->each_cmd[variables->i].files[c_of_s].files) == 1)
		my_struct->each_cmd[variables->i].files[c_of_s].files = ft_strdup("");
	return 0;
}

int	rediraction_calculate_output(t_all *my_struct, t_var *variables, int var, int c_of_s)
{

	while (my_struct->tmp_cmd[variables->j] \
		&& my_struct->tmp_cmd[variables->j] != 3
		&& !ft_isalnum(my_struct->tmp_cmd[variables->j]) \
		&& (my_struct->tmp_cmd[variables->j] == 2
			|| my_struct->tmp_cmd[variables->j] == 5))
	{
		if(my_struct->tmp_cmd[variables->j] == 2)
		{
			while (my_struct->tmp_cmd[variables->j] == 2)
			{
				my_struct->each_cmd[variables->i].files[c_of_s].number_of_O++;
				variables->j++;
			}
		}
		if(my_struct->tmp_cmd[variables->j] == 5)
		{
			while (my_struct->tmp_cmd[variables->j] == 5)
			{
				my_struct->each_cmd[variables->i].files[c_of_s].number_of_I++;
				variables->j++;
			}
		}
		if(my_struct->tmp_cmd[variables->j] == 0 \
		|| my_struct->tmp_cmd[variables->j] == 3 \
		|| ft_isalnum(my_struct->tmp_cmd[variables->j]) \
		|| (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O \
		&& my_struct->each_cmd[variables->i].files[c_of_s].number_of_I))
			break;
		variables->j++;
	}
	while (my_struct->tmp_cmd[variables->j] && my_struct->tmp_cmd[variables->j] == 3)
		variables->j++;
	var = variables->j;
	while (my_struct->tmp_cmd[var]
		&& my_struct->tmp_cmd[var] != 2
		&& my_struct->tmp_cmd[var] != 5
		&& my_struct->tmp_cmd[var] != 3)
		{
			if(my_struct->tmp_cmd[var] == 34 || my_struct->tmp_cmd[var] == 39)
				my_struct->each_cmd[variables->i].files[c_of_s].HERDOC_OPTION = 1;
			var++;
		}
	return (var);
}

int	rediraction_calculate_input(t_all *my_struct, t_var *variables, int var, int c_of_s)
{

	while (my_struct->tmp_cmd[variables->j] \
		&& my_struct->tmp_cmd[variables->j] != 3 \
		&& !ft_isalnum(my_struct->tmp_cmd[variables->j]) \
		&& (my_struct->tmp_cmd[variables->j] == 2 \
		|| my_struct->tmp_cmd[variables->j] == 5))
	{
		if(my_struct->tmp_cmd[variables->j] == 5)
		{
			while (my_struct->tmp_cmd[variables->j] == 5)
			{
				my_struct->each_cmd[variables->i].files[c_of_s].number_of_I++;
				variables->j++;
			}
		}
		if(my_struct->tmp_cmd[variables->j] == 2)
		{
			while (my_struct->tmp_cmd[variables->j] == 2)
			{
				my_struct->each_cmd[variables->i].files[c_of_s].number_of_O++;
				variables->j++;
			}
		}
		if(my_struct->tmp_cmd[variables->j] == 0 \
		|| my_struct->tmp_cmd[variables->j] == 3 \
		|| ft_isalnum(my_struct->tmp_cmd[variables->j])\
		|| (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O \
		&& my_struct->each_cmd[variables->i].files[c_of_s].number_of_I))
			break;
		variables->j++;
	}
	while (my_struct->tmp_cmd[variables->j] && my_struct->tmp_cmd[variables->j] == 3)
		variables->j++;
	var = variables->j;
	while (my_struct->tmp_cmd[var]
		&& my_struct->tmp_cmd[var] != 2
		&& my_struct->tmp_cmd[var] != 5
		&& my_struct->tmp_cmd[var] != 3)
		{
			if(my_struct->tmp_cmd[var] == 34 || my_struct->tmp_cmd[var] == 39)
				my_struct->each_cmd[variables->i].files[c_of_s].HERDOC_OPTION = 1;
			var++;
		}
	return (var);
}
void	 commande_and_args(t_all *my_struct, t_var *variables, int var)
{
	var = variables->j;
	variables->c = variables->j - 1;
	while (my_struct->tmp_cmd[var] && (my_struct->tmp_cmd[var] != 2 && my_struct->tmp_cmd[var] != 5))
		var++;
	while (variables->j < var)
	{
		if (my_struct->tmp_cmd[variables->j] == 34 && my_struct->status != IN_COTE)
		{
			if(my_struct->status == IN_DCOTE)
				my_struct->status = OUTSIDE;
			else
				my_struct->status = IN_DCOTE;
		}
		else if (my_struct->tmp_cmd[variables->j] == 39 && my_struct->status != IN_DCOTE)
		{
			if(my_struct->status == IN_COTE)
				my_struct->status = OUTSIDE;
			else
				my_struct->status = IN_COTE;
		}
		else if (my_struct->tmp_cmd[variables->j] == '$' \
		&& my_struct->tmp_cmd[variables->j + 1] \
		&& my_struct->tmp_cmd[variables->j + 1] != ' ' \
		&& my_struct->tmp_cmd[variables->j + 1] != 3)
		{
			variables->c++;
			my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,\
			ft_substr(my_struct->tmp_cmd, variables->c, variables->j - variables->c));
			variables->c = variables->j;
			if(my_struct->tmp_cmd[variables->j + 1])
				my_struct->the_commande =  variables_parceen_utils\
				(my_struct->tmp_cmd, my_struct->the_commande, my_struct, variables);
		}
		variables->j++;
	}
	variables->c++;
	my_struct->the_commande = ft_strjoin(my_struct->the_commande, ft_substr(my_struct->tmp_cmd, \
		variables->c, variables->j - variables->c));
	variables->j = var - 1;
}

void	if_rediraction_is_existe(t_all *my_struct, t_var *variables, int var)
{
	if (ft_strchr(my_struct->tmp_cmd, 2)
		|| ft_strchr(my_struct->splite_pipe[variables->i], 5))
	{
		var = 0;
		while (my_struct->tmp_cmd[variables->j])
		{
			if (my_struct->tmp_cmd[variables->j] == 2
				|| my_struct->tmp_cmd[variables->j] == 5)
			{
				while (my_struct->tmp_cmd[variables->j] == 2)
					variables->j++;
				var++;
			}
			if(!my_struct->tmp_cmd[variables->j])
				break;
			variables->j++;
		}
		my_struct->each_cmd[variables->i].files = ft_calloc(sizeof(t_files),
				(var + 1));
	}
}

int	any_commde_parceen(t_all *my_struct, t_var *variables, int var,
		int c_of_s)
{
	int i;
	if (my_struct->tmp_cmd[variables->j] && \
	my_struct->tmp_cmd[variables->j] == 2)
	{
		initialisaion(my_struct, variables, c_of_s);
		var = rediraction_calculate_output(my_struct, variables,  var, c_of_s);
		i = inistialisation_output(my_struct, variables, c_of_s, var);
		if(i == -1)
			return -1;
		if(i == -2)
			return -2;
		c_of_s++;
		variables->j = var - 1;
	}
	else if (my_struct->tmp_cmd[variables->j]\
	 && my_struct->tmp_cmd[variables->j] == 5)
	{
		initialisaion(my_struct, variables, c_of_s);
		var = rediraction_calculate_input(my_struct, variables, var, c_of_s);
		i = inistialisation_input(my_struct, variables, c_of_s, var);
		if(i == -1)
			return -1;
		if(i == -2)
			return -2;
		c_of_s++;
		variables->j = var - 1;
	}
	else if (my_struct->tmp_cmd[variables->j] \
	&& my_struct->tmp_cmd[variables->j] != 5
			&& my_struct->tmp_cmd[variables->j] != 2)
		commande_and_args(my_struct, variables, var);
	return c_of_s;
}

void qouts(t_all *my_struct, t_var *variables, int var, int c_of_s)
{
	while (variables->j < var)
	{
		if (my_struct->tmp_cmd[variables->j] == 34 \
		&& my_struct->status != IN_COTE)
		{
			if(my_struct->status == IN_DCOTE)
			{
				my_struct->each_cmd[variables->i].files[c_of_s].files = \
				ft_strjoin(my_struct->each_cmd[variables->i].files[c_of_s].files, "");
				my_struct->status = OUTSIDE;
			}
			else
				my_struct->status = IN_DCOTE;
			variables->c++;
			my_struct->each_cmd[variables->i].files[c_of_s].files = \
			ft_strjoin(my_struct->each_cmd[variables->i].files[c_of_s].files, \
			ft_substr(my_struct->tmp_cmd, \
			variables->c, variables->j - variables->c));
			variables->c = variables->j;
		}
		else if (my_struct->tmp_cmd[variables->j] == 39 \
		&& my_struct->status != IN_DCOTE)
		{
			if(my_struct->status == IN_COTE)
			{
				my_struct->status = OUTSIDE;
				my_struct->each_cmd[variables->i].files[c_of_s].files = \
				ft_strjoin(my_struct->each_cmd[variables->i].files[c_of_s].files, "");
			}
			else
				my_struct->status = IN_COTE;
			variables->c++;
			my_struct->each_cmd[variables->i].files[c_of_s].files = \
			ft_strjoin(my_struct->each_cmd[variables->i].files[c_of_s].files, ft_substr(my_struct->tmp_cmd, \
			variables->c, variables->j - variables->c));
			variables->c = variables->j;
		}
		else if ( my_struct->tmp_cmd[variables->j] == '$' \
		&& my_struct->tmp_cmd[variables->j + 1] \
		&& my_struct->tmp_cmd[variables->j + 1] != ' ' \
		&& my_struct->tmp_cmd[variables->j + 1] != 3 \
		&& my_struct->each_cmd[variables->i].files[c_of_s].HERDOC == 0)
		{
			variables->c++;
			my_struct->each_cmd[variables->i].files[c_of_s].files = ft_strjoin_v2(my_struct->each_cmd[variables->i].files[c_of_s].files,\
			ft_substr(my_struct->tmp_cmd, variables->c, variables->j - variables->c));
			variables->c = variables->j;
			if(my_struct->tmp_cmd[variables->j + 1])
				my_struct->each_cmd[variables->i].files[c_of_s].files =  variables_parceen_utils\
				(my_struct->tmp_cmd, my_struct->each_cmd[variables->i].files[c_of_s].files, my_struct, variables);
		}
		variables->j++;
	}
	variables->c++;
	my_struct->each_cmd[variables->i].files[c_of_s].files = \
	ft_strjoin(my_struct->each_cmd[variables->i].files[c_of_s].files, \
	ft_substr(my_struct->tmp_cmd, variables->c, variables->j - variables->c));
}

void qouts_comnde(t_all *my_struct, t_var *variables, int var)
{
	my_struct->each_cmd[variables->i].cmd = ft_split(my_struct->the_commande,
		3);
	free(my_struct->tmp_cmd);
	my_struct->tmp_cmd = 0;
	var = 0;
	int cas = 0;
	while(my_struct->each_cmd[variables->i].cmd[var])
	{
		// int i = 0;
		// while (my_struct->each_cmd[variables->i].cmd[var][i])
		// {
		// 	printf("[%d]\n", my_struct->the_commande[i]);
		// 	i++;
		// }
		variables->j = 0;
		variables->c = -1;
		my_struct->tmp_cmd = ft_calloc(1, 1);
		while (my_struct->each_cmd[variables->i].cmd[var][variables->j])
		{
			if (my_struct->each_cmd[variables->i].cmd[var][variables->j] == 34 \
			&& my_struct->status != IN_COTE)
			{
				if(my_struct->status == IN_DCOTE)
				{
					my_struct->tmp_cmd = ft_strjoin(my_struct->tmp_cmd, "");
					my_struct->status = OUTSIDE;
				}
				else
					my_struct->status = IN_DCOTE;
				variables->c++;
				my_struct->tmp_cmd = ft_strjoin(my_struct->tmp_cmd, ft_substr(my_struct->each_cmd[variables->i].cmd[var], \
				variables->c, variables->j - variables->c));
				variables->c = variables->j;
			}
			else if (my_struct->each_cmd[variables->i].cmd[var][variables->j] == 39 \
			&& my_struct->status != IN_DCOTE)
			{
				if(my_struct->status == IN_COTE)
				{
					my_struct->status = OUTSIDE;
					my_struct->tmp_cmd = ft_strjoin(my_struct->tmp_cmd, "");
				}
				else
					my_struct->status = IN_COTE;
				variables->c++;
				my_struct->tmp_cmd = ft_strjoin(my_struct->tmp_cmd, ft_substr(my_struct->each_cmd[variables->i].cmd[var], \
				variables->c, variables->j - variables->c));
				variables->c = variables->j;
			}
			variables->j++;
		}
		variables->c++;
		my_struct->tmp_cmd = ft_strjoin(my_struct->tmp_cmd, ft_substr(my_struct->each_cmd[variables->i].cmd[var], \
				variables->c, variables->j - variables->c));
		free(my_struct->each_cmd[variables->i].cmd[var]);
		my_struct->each_cmd[variables->i].cmd[var] = 0;
		if(!(ft_strchr(my_struct->tmp_cmd, 7) && \
		ft_strlen(my_struct->tmp_cmd) == 1))
		{
			my_struct->each_cmd[variables->i].cmd[cas] = ft_strdup(my_struct->tmp_cmd);
			cas++;
		}
		free(my_struct->tmp_cmd);
		my_struct->tmp_cmd = 0;
		var++;
	}
}

int	rederaction_parccen(t_all *my_struct, t_var *variables)
{
	int	c_of_s;
	int	var;

	c_of_s = 0;
	var = 0;
	variables->i = 0;
	my_struct->fils_descreprot = 0;
	while (my_struct->splite_pipe[variables->i])
	{
		my_struct->status = OUTSIDE;
		my_struct->tmp_cmd = ft_strdup(my_struct->splite_pipe[variables->i]);
		variables->j = 0;
		my_struct->the_commande = ft_calloc(1, 1);
		if_rediraction_is_existe(my_struct, variables, var);
		c_of_s = 0;
		variables->j = 0;
		while (my_struct->tmp_cmd[variables->j])
		{
			c_of_s = any_commde_parceen(my_struct, variables, var, c_of_s);
			if(c_of_s == -1)
				return -1;
			if(c_of_s == -2)
				return -2;
			variables->j++;
		}
		// int i = 0;
		// while (my_struct->the_commande[i])
		// {
		// 	printf("{%d}\n", my_struct->the_commande[i]);
		// 	i++;
		// }
		qouts_comnde(my_struct, variables, var);
		free(my_struct->splite_pipe[variables->i]);
		my_struct->splite_pipe[variables->i] = 0;
		free(my_struct->the_commande);
		my_struct->the_commande = 0;
		variables->i++;
	}
	free(my_struct->splite_pipe);
	// exit(0);
	return 0;
}

int	fix_arg(t_all *my_struct)
{
	t_var variables;
	variables.i = 0;
	variables.j = 0;
	variables.c = -1;
	char splite[2];
	splite[0] = 3;
	splite[1] = '\0';
	my_struct->number_of_pipes = 1;
	my_struct->the_commande = 0;
	my_struct->the_commande = ft_calloc(1, 1);
	variables.i = parccen_part(my_struct, &variables, splite);
	if(variables.i == -1)
		return 2;
	if(variables.i == 258)
		return 258;
	free(my_struct->fix_cmd);
	my_struct->splite_pipe = ft_split(my_struct->the_commande, 4);
	free(my_struct->the_commande);
	my_struct->the_commande = 0;
	variables.i = 0;
	my_struct->each_cmd = ft_calloc(sizeof(t_each_command),\
		my_struct->number_of_pipes + 1);
	variables.i = rederaction_parccen(my_struct, &variables);
	if(variables.i == -1)
		return 258;
	if(variables.i == -2)
		return 1;
	return 0;
}