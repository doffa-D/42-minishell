/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/04/28 12:54:57 by nouakhro         ###   ########.fr       */
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
	if ((my_struct->fix_cmd[variables->i][variables->j] == 34) && my_struct->status != IN_COTE)
	{
		if (my_struct->fix_cmd[variables->i][variables->j] == 34 && my_struct->status == IN_DCOTE)
			my_struct->status = OUTSIDE;
		else
			my_struct->status = IN_DCOTE;
	}
	if ((my_struct->fix_cmd[variables->i][variables->j] == 39) && my_struct->status != IN_DCOTE)
	{
		if (my_struct->fix_cmd[variables->i][variables->j] == 39 && my_struct->status == IN_COTE)
			my_struct->status = OUTSIDE;
		else
			my_struct->status = IN_COTE;
	}
	return (0);
}

char *my_getenv(t_list *head , char *var)
{
	int j = 0;
	(void)var;
	int i = 0;
	// char *expande;
	char *expande_variable = ft_calloc(1, 2);
	expande_variable[0] = 7;
	expande_variable[1] = 0;
	while (head)
	{
		if(*(char *)head->content == var[0])
		{
			j = 0;
			while(((char *)head->content)[j] == var[j] || ((char *)head->content)[j] == '=')
			{
				if(((char *)head->content)[j] == '=' && !var[j])
				{
					expande_variable = ft_substr(head->content, j + 1, ft_strlen(head->content + (j + 1)));
					i = 0;
					while (expande_variable[i])
					{
						if(expande_variable[i] == ' ')
							expande_variable[i] = 3;
						i++;
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

void	variables_parceen(t_all *my_struct, t_var *variables)
{
	int		var;
	char	*variable;

	var = variables->j + 1;
	if(my_struct->each_cmd[variables->i].cmd[var] == 0)
		return ;
	my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,
		ft_substr(my_struct->each_cmd[variables->i].cmd[var], variables->c, \
        variables->j - variables->c));
	while (my_struct->each_cmd[variables->i].cmd[var][var]
		&& (ft_isalpha(my_struct->each_cmd[variables->i].cmd[var][var])
			|| ft_isdigit(my_struct->each_cmd[variables->i].cmd[var][var])))
		var++;
	// printf("((%s))\n", my_struct->the_commande);
	if (my_struct->status == IN_DCOTE || my_struct->status == OUTSIDE)
	{
		if(ft_isdigit(my_struct->each_cmd[variables->i].cmd[var][variables->j + 1]) && my_struct->each_cmd[variables->i].cmd[var][variables->j + 1] != '_')
		{
			variables->j++;
			variable = ft_substr(my_struct->each_cmd[variables->i].cmd[var], variables->j + 1,
					(var - (variables->j + 1)));
			my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, \
			variable);
			variables->j = var - 1;
		}
		else if(ft_isalpha(my_struct->each_cmd[variables->i].cmd[var][variables->j + 1]) || my_struct->each_cmd[variables->i].cmd[var][variables->j + 1] == '_')
		{
			variable = ft_substr(my_struct->each_cmd[variables->i].cmd[var], variables->j + 1,
					(var - (variables->j + 1)));
			variable = my_getenv(my_struct->list,variable);
			if (variable)
			{
				my_struct->the_commande = ft_strjoin(my_struct->the_commande, \
					variable);
			}
			variables->j = var - 1;
		}
	}
	if (my_struct->status == IN_COTE)
	{
		variable = ft_substr(my_struct->each_cmd[variables->i].cmd[var], variables->j,
				(var - variables->j));
		my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, \
			variable);
		variables->j = var - 1;
	}

}

void	variables_parceen_utils(t_all *my_struct, t_var *variables, int var)
{
	if (ft_isalnum(my_struct->each_cmd[variables->i].cmd[var][variables->j + 1]))
	{
		if (my_struct->each_cmd[variables->i].cmd[var][variables->j + 1])
		{
			variables->c++;
			variables_parceen(my_struct, variables);
			variables->c = variables->j;
		}
	}
// 	export a=" b"$
// echo foo $a bar$
	else
	{
		if(my_struct->each_cmd[variables->i].cmd[var][variables->j + 1] == '?')
		{
			if(my_struct->status != IN_COTE)
			{
				variables->c++;
				my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,
				ft_substr(my_struct->each_cmd[variables->i].cmd[var], variables->c, \
				variables->j - variables->c));
				variables->j++;
				my_struct->the_commande = ft_strjoin(my_struct->the_commande,ft_itoa(my_struct->exit_status));
				variables->c = variables->j;
			}
		}
		else if(my_struct->status == OUTSIDE && (my_struct->each_cmd[variables->i].cmd[var][variables->j + 1] == 34 || my_struct->each_cmd[variables->i].cmd[var][variables->j + 1] == 39))
			variables->c = variables->j;
		else if(my_struct->each_cmd[variables->i].cmd[var][variables->j + 1] != 34 && my_struct->each_cmd[variables->i].cmd[var][variables->j + 1] != 39)
		{
			variables->j++;
			variables->c = variables->j;
		}

	}
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
			if((my_struct->fix_cmd[variables->i][variables->j] == 4 && !my_struct->fix_cmd[variables->i + 1] && !my_struct->fix_cmd[variables->i][variables->j + 1]) || \
			(my_struct->fix_cmd[variables->i][variables->j] == 4 && variables->i == 0))
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				return 258;
			}
			variables->j++;
		}
		my_struct->the_commande = ft_strjoin(my_struct->the_commande, my_struct->fix_cmd[variables->i]);
		if(my_struct->fix_cmd[variables->i +1])
			my_struct->the_commande = ft_strjoin(my_struct->the_commande, splite);
		free(my_struct->fix_cmd[variables->i]);
		my_struct->fix_cmd[variables->i] = 0;
		variables->i++;
	}
	if(my_struct->status != OUTSIDE)
	{
		my_struct->status = fork();
		if(my_struct->status == 0)
		{
			dup2(2, 1);
			printf("minishell: unexpected EOF while looking for matching\n");
			exit(1);
		}
		wait(&my_struct->status);
		return -1;
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
}

int 	inistialisation_input(t_all *my_struct, t_var *variables, int c_of_s,
		int var)
{
	int checher = 0;
	if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_I > 2)
		checher = 1;
	if(my_struct->each_cmd[variables->i].files[c_of_s].number_of_O \
	&& my_struct->each_cmd[variables->i].files[c_of_s].number_of_I)
		checher = 1;
	if(!my_struct->tmp_cmd[variables->j])
		checher = 1;
	else
	{
		variables->c = variables->j - 1;
		my_struct->each_cmd[variables->i].files[c_of_s].files = ft_calloc(1, 1);
		qouts(my_struct, variables, var , c_of_s);
		if(ft_strchr(my_struct->each_cmd[variables->i].files[c_of_s].files, 7) && \
		ft_strlen(my_struct->each_cmd[variables->i].files[c_of_s].files) == 1)
		{
			checher = fork();
			if(checher == 0)
			{
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				exit(1);
			}
			wait(&checher);
			return -1;
		}
	}
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
	if(ft_strchr(my_struct->each_cmd[variables->i].files[c_of_s].files, 6) && \
	ft_strlen(my_struct->each_cmd[variables->i].files[c_of_s].files) == 1)
		my_struct->each_cmd[variables->i].files[c_of_s].files = ft_strdup("");
	if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_I == 1)
		my_struct->each_cmd[variables->i].files[c_of_s].INPUT = 1;
	else if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_I == 2)
		my_struct->each_cmd[variables->i].files[c_of_s].HERDOC = 1;
	return 0;
}

int		inistialisation_output(t_all *my_struct, t_var *variables, int c_of_s,
		int var)
{
	int checher = 0;
	if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O > 2)
		checher = 1;
	if(my_struct->each_cmd[variables->i].files[c_of_s].number_of_O \
	&& my_struct->each_cmd[variables->i].files[c_of_s].number_of_I)
		checher = 1;
	if(!my_struct->tmp_cmd[variables->j])
		checher = 1;
	else
	{
		variables->c = variables->j - 1;
		my_struct->each_cmd[variables->i].files[c_of_s].files = ft_calloc(1, 1);
		qouts(my_struct, variables, var , c_of_s);
		printf("[%s]\n", my_struct->each_cmd[c_of_s].files->files);
		if(ft_strchr(my_struct->each_cmd[variables->i].files[c_of_s].files, 7) && \
		ft_strlen(my_struct->each_cmd[variables->i].files[c_of_s].files) == 1)
		{
			checher = fork();
			if(checher == 0)
			{
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				exit(1);
			}
			wait(&checher);
			return -1;
		}
	}
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
	if(ft_strchr(my_struct->each_cmd[variables->i].files[c_of_s].files, 6) && \
	ft_strlen(my_struct->each_cmd[variables->i].files[c_of_s].files) == 1)
		my_struct->each_cmd[variables->i].files[c_of_s].files = ft_strdup("");
	else if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O == 2)
		my_struct->each_cmd[variables->i].files[c_of_s].APPEND = 1;
	else if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O == 1)
		my_struct->each_cmd[variables->i].files[c_of_s].OUTPUT = 1;
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
		var++;
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
		|| !ft_isalnum(my_struct->tmp_cmd[variables->j])\
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
		var++;
	// printf("1[%d]\n",my_struct->tmp_cmd[var-1]);
	return (var);
}
void	commande_and_args(t_all *my_struct, t_var *variables, int var)
{
	var = variables->j;
	while (my_struct->tmp_cmd[var]
		&& (my_struct->tmp_cmd[var] != 2
			&& my_struct->tmp_cmd[var] != 5))
		var++;
	my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,\
	            ft_substr(my_struct->tmp_cmd,\
	            variables->j, var\
	            - variables->j));
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
	if (my_struct->tmp_cmd[variables->j] == 2)
	{
		initialisaion(my_struct, variables, c_of_s);
		var = rediraction_calculate_output(my_struct, variables,  var, c_of_s);
		if(inistialisation_output(my_struct, variables, c_of_s, var))
			return -1;
		c_of_s++;
		variables->j = var - 1;
	}
	else if (my_struct->tmp_cmd[variables->j] == 5)
	{
		initialisaion(my_struct, variables, c_of_s);
		var = rediraction_calculate_input(my_struct, variables, var, c_of_s);
		if(inistialisation_input(my_struct, variables, c_of_s, var))
			return -1;
		c_of_s++;
		variables->j = var - 1;
	}
	else if (my_struct->tmp_cmd[variables->j] != 5
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
			// printf("%s\n",my_struct->each_cmd[variables->i].files[c_of_s].files);
			variables->c = variables->j;
		}
		variables->j++;
	}
	variables->c++;
	my_struct->each_cmd[variables->i].files[c_of_s].files = \
	ft_strjoin(my_struct->each_cmd[variables->i].files[c_of_s].files, \
	ft_substr(my_struct->tmp_cmd, \
		variables->c, variables->j - variables->c));
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
			if(my_struct->each_cmd[variables->i].cmd[var][variables->j] == '$')
				variables_parceen_utils(my_struct, variables, var);
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
	while (my_struct->splite_pipe[variables->i])
	{
		char str[2];
		str[0] = 6;
		str[1] = 0;
		variables->j = 0;
		variables->c = -1;
		my_struct->tmp_cmd = 0;
		my_struct->tmp_cmd = ft_calloc(1, 1);
		my_struct->status = OUTSIDE;
		// while (my_struct->splite_pipe[variables->i][variables->j])
		// {
		// 	if ((my_struct->splite_pipe[variables->i][variables->j] == 34) && my_struct->status != IN_COTE)
		// 	{
		// 		if (my_struct->splite_pipe[variables->i][variables->j] == 34 && my_struct->status == IN_DCOTE)
		// 			my_struct->status = OUTSIDE;
		// 		else
		// 			my_struct->status = IN_DCOTE;
		// 	}
		// 	if ((my_struct->splite_pipe[variables->i][variables->j] == 39) && my_struct->status != IN_DCOTE)
		// 	{
		// 		if (my_struct->splite_pipe[variables->i][variables->j] == 39 && my_struct->status == IN_COTE)
		// 			my_struct->status = OUTSIDE;
		// 		else
		// 			my_struct->status = IN_COTE;
		// 	}
		// 	if(my_struct->splite_pipe[variables->i][variables->j] == '$')
		// 		variables_parceen_utils(my_struct, variables, &my_struct->tmp_cmd);
		// 	variables->j++;
		// }
		// variables->c++;
		// my_struct->tmp_cmd = ft_strjoin(my_struct->tmp_cmd, ft_substr(my_struct->splite_pipe[variables->i], \
		// 		variables->c, variables->j - variables->c));
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
			variables->j++;
		}
		// printf("%s\n", my_struct->the_commande);
		qouts_comnde(my_struct, variables, var);
		free(my_struct->splite_pipe[variables->i]);
		free(my_struct->the_commande);
		my_struct->the_commande = 0;
		my_struct->splite_pipe[variables->i] = 0;
		variables->i++;
	}
	free(my_struct->splite_pipe);
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
	// while(my_struct->splite_pipe[variables.i])
	// {
	// 	printf("[%s]\n", my_struct->splite_pipe[variables.i]);
	// 	variables.i++;
	// }
	// exit(0);
	my_struct->each_cmd = ft_calloc(sizeof(t_each_command),\
		my_struct->number_of_pipes + 1);
	if(rederaction_parccen(my_struct, &variables))
		return 258;
	return 0;
}