/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/04/24 16:39:31 by nouakhro         ###   ########.fr       */
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
	char str[2];
	str[0] = 6;
	str[1] = 0;
	if ((my_struct->fix_cmd[variables->i][variables->j] == 34)
		&& my_struct->status != IN_COTE)
	{
		variables->c++;
		if (my_struct->fix_cmd[variables->i][variables->j] == 34
			&& my_struct->status == IN_DCOTE)
		{
			my_struct->status = OUTSIDE;
			if(ft_strlen(my_struct->fix_cmd[variables->i]) == 2)
				my_struct->the_commande = ft_strjoin(my_struct->the_commande, str);
		}
		else
			my_struct->status = IN_DCOTE;
		my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, \
			ft_substr(my_struct->fix_cmd[variables->i], variables->c, \
            variables->j - variables->c));
		variables->c = variables->j;
	}
	if ((my_struct->fix_cmd[variables->i][variables->j] == 39)
		&& my_struct->status != IN_DCOTE)
	{
		variables->c++;
		if (my_struct->fix_cmd[variables->i][variables->j] == 39
			&& my_struct->status == IN_COTE)
		{
			my_struct->status = OUTSIDE;
			if(ft_strlen(my_struct->fix_cmd[variables->i]) == 2)
				my_struct->the_commande = ft_strjoin(my_struct->the_commande, str);
		}
		else
			my_struct->status = IN_COTE;
		my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,
			ft_substr(my_struct->fix_cmd[variables->i], variables->c, \
            variables->j - variables->c));
		variables->c = variables->j;
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

char *my_getenv(t_list *head , char *var)
{
	int j = 0;
	(void)var;
	int i = 0;
	char *expande_variable = ft_calloc(1, 1);
	while (head)
	{
		if(*(char *)head->content == var[0])
		{
			j = 0;
			while(((char *)head->content)[j] == var[j] || ((char *)head->content)[j] == '=')
			{
				if(((char *)head->content)[j] == '=')
				{
					expande_variable = ft_substr(head->content, j + 1, ft_strlen(head->content + (j + 1)));
					return(expande_variable);
				}
				j++;
			}
		}
		i++;
		head = head->next;
	}
	return(expande_variable);
}

void	variables_parceen(t_all *my_struct, t_var *variables)
{
	int		var;
	char	*variable;

	var = variables->j + 1;
	my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,
		ft_substr(my_struct->fix_cmd[variables->i], variables->c, \
        variables->j - variables->c));
	while (my_struct->fix_cmd[variables->i][var]
		&& (ft_isalpha(my_struct->fix_cmd[variables->i][var])
			|| ft_isdigit(my_struct->fix_cmd[variables->i][var])))
		var++;
	
	if (my_struct->status == IN_DCOTE || my_struct->status == OUTSIDE)
	{
		if(ft_isdigit(my_struct->fix_cmd[variables->i][variables->j + 1]))
		{
			variables->j++;
			variable = ft_substr(my_struct->fix_cmd[variables->i], variables->j + 1,
					(var - (variables->j + 1)));
			my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, \
			variable);
			variables->j = var - 1;
		}
		variable = ft_substr(my_struct->fix_cmd[variables->i], variables->j + 1,
				(var - (variables->j + 1)));
		variable = my_getenv(my_struct->list,variable);
		if (variable && *variable)
		{
			my_struct->the_commande = ft_strjoin(my_struct->the_commande, \
				variable);

		}
		variables->j = var - 1;
	}
	if (my_struct->status == IN_COTE)
	{
		variable = ft_substr(my_struct->fix_cmd[variables->i], variables->j,
				(var - variables->j));
		my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, \
			variable);
		variables->j = var - 1;
	}

}

void	variables_parceen_utils(t_all *my_struct, t_var *variables)
{
	if (ft_isalnum(my_struct->fix_cmd[variables->i][variables->j + 1]))
	{
		if (my_struct->fix_cmd[variables->i][variables->j + 1])
		{
			variables->c++;
			variables_parceen(my_struct, variables);
			variables->c = variables->j;
		}
	}
	else
	{
		if(my_struct->fix_cmd[variables->i][variables->j + 1] == '?')
		{
			variables->j++;
			my_struct->the_commande = ft_strjoin(my_struct->the_commande,ft_itoa(my_struct->exit_status));
			variables->c = variables->j;
		}
		else if(my_struct->status == OUTSIDE && (my_struct->fix_cmd[variables->i][variables->j + 1] == 34 || my_struct->fix_cmd[variables->i][variables->j + 1] == 39))
			variables->c = variables->j;
	}
}

int	parccen_part(t_all *my_struct, t_var *variables, char *splite)
{
	while (my_struct->fix_cmd[variables->i])
	{
		variables->j = 0;
		variables->c = -1;
		my_struct->status = OUTSIDE;
		while (my_struct->fix_cmd[variables->i][variables->j])
		{
			quote_and_dqout(my_struct, variables);
			pipe_and_rederaction_parceen(my_struct, variables);
			if (my_struct->fix_cmd[variables->i][variables->j] == '$'
				&& my_struct->fix_cmd[variables->i][variables->j + 1])
				variables_parceen_utils(my_struct, variables);
			variables->j++;
		}
		if(my_struct->status != OUTSIDE)
		{
			ft_putstr_fd("error : inclosed qouts\n", 2);
			return -1;
		}
		if (my_struct->status == OUTSIDE)
		{
			variables->c++;
			my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, \
				ft_substr(my_struct->fix_cmd[variables->i], variables->c, \
				variables->j - variables->c));
		}
		my_struct->the_commande = ft_strjoin(my_struct->the_commande, splite);
		free(my_struct->fix_cmd[variables->i]);
		my_struct->fix_cmd[variables->i] = 0;
		variables->i++;
	}
	return 1;
}


void	initialisaion(t_all *my_struct, t_var *variables, int c_of_s)
{
	// int buckup = variables->j;
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
	if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_I > 2)
	{
		my_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSI = 1;
		ft_putstr_fd("bash: syntax error near unexpected token `<<'\n", 2);
		return(-1);
	}
	else if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O > 1)
	{
		my_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSO = 1;
		ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
		return(-1);
	}
	else if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O == 1)
	{
		my_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSO = 1;
		ft_putstr_fd("bash: syntax error near unexpected token `>'\n", 2);
		return(-1);
	}
	my_struct->each_cmd[variables->i].files[c_of_s].files = \
    ft_substr(my_struct->splite_pipe[variables->i],variables->j, var - variables->j);
	if(ft_strchr(my_struct->each_cmd[variables->i].files[c_of_s].files, 6) && \
	ft_strlen(my_struct->each_cmd[variables->i].files[c_of_s].files) == 1)
		my_struct->each_cmd[variables->i].files[c_of_s].files = ft_strdup("");
	if(!my_struct->each_cmd[variables->i].files[c_of_s].files)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return(-1);
	}
	if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_I == 1)
		my_struct->each_cmd[variables->i].files[c_of_s].INPUT = 1;
	else if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_I == 2)
		my_struct->each_cmd[variables->i].files[c_of_s].HERDOC = 1;
	return 0;
}

int		inistialisation_output(t_all *my_struct, t_var *variables, int c_of_s,
		int var)
{
	if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O > 2)
	{
		my_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSO = 1;
		ft_putstr_fd("minshell : syntax error near unexpected token `>>'\n", 2);
		return(-1);
	}
	else if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_I > 1)
	{
		my_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSI = 1;
		ft_putstr_fd("minshell : syntax error near unexpected token `<<'\n", 2);
		return(-1);
	}
	else if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_I == 1)
	{
		my_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSI = 1;
		ft_putstr_fd("minshell : syntax error near unexpected token `<'\n", 2);
		return(-1);
	}
	// printf("TTT\n");
	my_struct->each_cmd[variables->i].files[c_of_s].files = \
    ft_substr(my_struct->splite_pipe[variables->i],variables->j, var - variables->j);
	if(ft_strchr(my_struct->each_cmd[variables->i].files[c_of_s].files, 6) && \
	ft_strlen(my_struct->each_cmd[variables->i].files[c_of_s].files) == 1)
		my_struct->each_cmd[variables->i].files[c_of_s].files = ft_strdup("");
	if(!my_struct->each_cmd[variables->i].files[c_of_s].files)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return(-1);
	}
	else if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O == 2)
		my_struct->each_cmd[variables->i].files[c_of_s].APPEND = 1;
	else if (my_struct->each_cmd[variables->i].files[c_of_s].number_of_O == 1)
		my_struct->each_cmd[variables->i].files[c_of_s].OUTPUT = 1;
	return 0;
}

int	rediraction_calculate_output(t_all *my_struct, t_var *variables, int var, int c_of_s)
{

	while (my_struct->splite_pipe[variables->i][variables->j]
		&& (my_struct->splite_pipe[variables->i][variables->j] == 2
			|| my_struct->splite_pipe[variables->i][variables->j] == 3
			|| my_struct->splite_pipe[variables->i][variables->j] == 5))
	{
		if(my_struct->splite_pipe[variables->i][variables->j] == 2)
		{
			while (my_struct->splite_pipe[variables->i][variables->j] == 2)
			{
				my_struct->each_cmd[variables->i].files[c_of_s].number_of_O++;
				variables->j++;
			}
		}
		if(my_struct->splite_pipe[variables->i][variables->j] == 5)
		{
			while (my_struct->splite_pipe[variables->i][variables->j] == 5)
			{
				my_struct->each_cmd[variables->i].files[c_of_s].number_of_I++;
				variables->j++;
			}
		}
		if(my_struct->each_cmd[variables->i].files[c_of_s].number_of_O \
		&& my_struct->each_cmd[variables->i].files[c_of_s].number_of_I)
			break;
		variables->j++;
	}
	var = variables->j;
	while (my_struct->splite_pipe[variables->i][var]
		&& my_struct->splite_pipe[variables->i][var] != 2
		&& my_struct->splite_pipe[variables->i][var] != 5
		&& my_struct->splite_pipe[variables->i][var] != 3)
		var++;
	return (var);
}

int	rediraction_calculate_input(t_all *my_struct, t_var *variables, int var, int c_of_s)
{

	while (my_struct->splite_pipe[variables->i][variables->j]
		&& (my_struct->splite_pipe[variables->i][variables->j] == 2
			|| my_struct->splite_pipe[variables->i][variables->j] == 3
			|| my_struct->splite_pipe[variables->i][variables->j] == 5))
	{
		if(my_struct->splite_pipe[variables->i][variables->j] == 5)
		{
			while (my_struct->splite_pipe[variables->i][variables->j] == 5)
			{
				my_struct->each_cmd[variables->i].files[c_of_s].number_of_I++;
				variables->j++;
			}
		}
		if(my_struct->splite_pipe[variables->i][variables->j] == 2)
		{
			while (my_struct->splite_pipe[variables->i][variables->j] == 2)
			{
				my_struct->each_cmd[variables->i].files[c_of_s].number_of_O++;
				variables->j++;
			}
		}
		if(my_struct->each_cmd[variables->i].files[c_of_s].number_of_O \
		&& my_struct->each_cmd[variables->i].files[c_of_s].number_of_I)
			break;
		variables->j++;
	}
	var = variables->j;
	while (my_struct->splite_pipe[variables->i][var]
		&& my_struct->splite_pipe[variables->i][var] != 2
		&& my_struct->splite_pipe[variables->i][var] != 5
		&& my_struct->splite_pipe[variables->i][var] != 3)
		var++;
	return (var);
}
void	commande_and_args(t_all *my_struct, t_var *variables, int var)
{
	var = variables->j;
	while (my_struct->splite_pipe[variables->i][var]
		&& (my_struct->splite_pipe[variables->i][var] != 2
			&& my_struct->splite_pipe[variables->i][var] != 5))
		var++;
	my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,\
	            ft_substr(my_struct->splite_pipe[variables->i],\
	            variables->j, var\
	            - variables->j));
	variables->j = var - 1;

}

void	if_rediraction_is_existe(t_all *my_struct, t_var *variables, int var)
{
	if (ft_strchr(my_struct->splite_pipe[variables->i], 2)
		|| ft_strchr(my_struct->splite_pipe[variables->i], 5))
	{
		var = 0;
		while (my_struct->splite_pipe[variables->i][variables->j])
		{
			if (my_struct->splite_pipe[variables->i][variables->j] == 2
				|| my_struct->splite_pipe[variables->i][variables->j] == 5)
			{
				while (my_struct->splite_pipe[variables->i][variables->j] == 2)
					variables->j++;
				var++;
			}
			if(!my_struct->splite_pipe[variables->i][variables->j])
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
	if (my_struct->splite_pipe[variables->i][variables->j] == 2)
	{
		initialisaion(my_struct, variables, c_of_s);
		var = rediraction_calculate_output(my_struct, variables,  var, c_of_s);
		if(inistialisation_output(my_struct, variables, c_of_s, var))
			return -1;
		c_of_s++;
		variables->j = var - 1;
	}
	else if (my_struct->splite_pipe[variables->i][variables->j] == 5)
	{
		initialisaion(my_struct, variables, c_of_s);
		var = rediraction_calculate_input(my_struct, variables, var, c_of_s);
		if(inistialisation_input(my_struct, variables, c_of_s, var))
			return -1;
		c_of_s++;
		variables->j = var - 1;
	}
	else if (my_struct->splite_pipe[variables->i][variables->j] != 5
			&& my_struct->splite_pipe[variables->i][variables->j] != 2)
		commande_and_args(my_struct, variables, var);
	return c_of_s;
}

int	rederaction_parccen(t_all *my_struct, t_var *variables)
{
	int	c_of_s;
	int	var;
	// int	k;

	c_of_s = 0;
	var = 0;
	while (my_struct->splite_pipe[variables->i])
	{
		variables->j = 0;
		my_struct->the_commande = ft_calloc(1, 1);
		if_rediraction_is_existe(my_struct, variables, var);
		c_of_s = 0;
		variables->j = 0;
		while (my_struct->splite_pipe[variables->i][variables->j])
		{
			c_of_s = any_commde_parceen(my_struct, variables, var, c_of_s);
			if(c_of_s == -1)
				return -1;
			variables->j++;
		}
		my_struct->each_cmd[variables->i].cmd = ft_split(my_struct->the_commande,
				3);
		var = 0;
		while(my_struct->each_cmd[variables->i].cmd[var])
		{
			if(ft_strchr(my_struct->each_cmd[variables->i].cmd[var], 6) && \
			ft_strlen(my_struct->each_cmd[variables->i].cmd[var]) == 1)
				my_struct->each_cmd[variables->i].cmd[var] = ft_strdup("");
			var++;
		}
		// if(my_struct->each_cmd[c_of_s].cmd && !*my_struct->each_cmd[c_of_s].cmd && my_struct->number_of_pipes > 1)
		// {
		// 	if(my_struct->number_of_pipes > 2)
		// 		ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
		// 	else
		// 		ft_putstr_fd("syntax error : only pipe\n", 2);
		// 	return(-1);
		// }
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
	if(parccen_part(my_struct, &variables, splite) == -1)
		return -1;
	free(my_struct->fix_cmd);
	my_struct->splite_pipe = ft_split(my_struct->the_commande, 4);
	// int i = 0;
	// while(my_struct->splite_pipe[i])
	// {
	// 	printf("[%s]\n", my_struct->splite_pipe[i]);
	// 	i++;
	// }
	free(my_struct->the_commande);
	my_struct->the_commande = 0;
	variables.i = 0;
	my_struct->each_cmd = ft_calloc(sizeof(t_each_command),\
		my_struct->number_of_pipes + 1);
	if(rederaction_parccen(my_struct, &variables))
		return -1;
	return 0;
}