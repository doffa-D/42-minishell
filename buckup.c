/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buckup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/05 20:29:34 by nouakhro         ###   ########.fr       */
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

int	quote_and_dqout(t_all *_struct, t_var *variables)
{
	char str[2];
	str[0] = 6;
	str[1] = 0;
	if ((_struct->fix_cmd[variables->i][variables->j] == 34)
		&& _struct->status != IN_COTE)
	{
		variables->c++;
		if (_struct->fix_cmd[variables->i][variables->j] == 34
			&& _struct->status == IN_DCOTE)
		{
			_struct->status = OUTSIDE;
			if(ft_strlen(_struct->fix_cmd[variables->i]) == 2)
				_struct->the_commande = ft_strjoin(_struct->the_commande, str);
		}
		else
			_struct->status = IN_DCOTE;
		_struct->the_commande = ft_strjoin_v2(_struct->the_commande, \
			ft_substr(_struct->fix_cmd[variables->i], variables->c, \
            variables->j - variables->c));
		variables->c = variables->j;
	}
	if ((_struct->fix_cmd[variables->i][variables->j] == 39)
		&& _struct->status != IN_DCOTE)
	{
		variables->c++;
		if (_struct->fix_cmd[variables->i][variables->j] == 39
			&& _struct->status == IN_COTE)
		{
			_struct->status = OUTSIDE;
			if(ft_strlen(_struct->fix_cmd[variables->i]) == 2)
				_struct->the_commande = ft_strjoin(_struct->the_commande, str);
		}
		else
			_struct->status = IN_COTE;
		_struct->the_commande = ft_strjoin_v2(_struct->the_commande,
			ft_substr(_struct->fix_cmd[variables->i], variables->c, \
            variables->j - variables->c));
		variables->c = variables->j;
	}
	return (variables->c);
}

void	pipe_and_rederaction_parceen(t_all *_struct, t_var *variables)
{
	if (_struct->fix_cmd[variables->i][variables->j] == '|'
		&& _struct->status == OUTSIDE)
	{
		_struct->fix_cmd[variables->i][variables->j] = 4;
		_struct->number_of_pipes++;
	}
	if (_struct->fix_cmd[variables->i][variables->j] == '>'
		&& _struct->status == OUTSIDE)
	{
		_struct->fix_cmd[variables->i][variables->j] = 2;
		_struct->if_rediraction = 1;
	}
	if (_struct->fix_cmd[variables->i][variables->j] == '<'
		&& _struct->status == OUTSIDE)
	{
		_struct->fix_cmd[variables->i][variables->j] = 5;
		_struct->if_rediraction = 1;
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
				if(((char *)head->content)[j] == '=' && !var[j])
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

void	variables_parceen(t_all *_struct, t_var *variables)
{
	int		var;
	char	*variable;

	var = variables->j + 1;
	_struct->the_commande = ft_strjoin_v2(_struct->the_commande,
		ft_substr(_struct->fix_cmd[variables->i], variables->c, \
        variables->j - variables->c));
	while (_struct->fix_cmd[variables->i][var]
		&& (ft_isalpha(_struct->fix_cmd[variables->i][var])
			|| ft_isdigit(_struct->fix_cmd[variables->i][var])))
		var++;
	if (_struct->status == IN_DCOTE || _struct->status == OUTSIDE)
	{
		if(ft_isdigit(_struct->fix_cmd[variables->i][variables->j + 1]) && _struct->fix_cmd[variables->i][variables->j + 1] != '_')
		{
			variables->j++;
			variable = ft_substr(_struct->fix_cmd[variables->i], variables->j + 1,
					(var - (variables->j + 1)));
			_struct->the_commande = ft_strjoin_v2(_struct->the_commande, \
			variable);
			variables->j = var - 1;
		}
		variable = ft_substr(_struct->fix_cmd[variables->i], variables->j + 1,
				(var - (variables->j + 1)));
		variable = my_getenv(_struct->list,variable);
		if (variable)
		{
			_struct->the_commande = ft_strjoin(_struct->the_commande, \
				variable);
		}
		variables->j = var - 1;
	}
	if (_struct->status == IN_COTE)
	{
		variable = ft_substr(_struct->fix_cmd[variables->i], variables->j,
				(var - variables->j));
		_struct->the_commande = ft_strjoin_v2(_struct->the_commande, \
			variable);
		variables->j = var - 1;
	}

}

void	variables_parceen_utils(t_all *_struct, t_var *variables)
{
	if (ft_isalnum(_struct->fix_cmd[variables->i][variables->j + 1]))
	{
		if (_struct->fix_cmd[variables->i][variables->j + 1])
		{
			variables->c++;
			variables_parceen(_struct, variables);
			variables->c = variables->j;
		}
	}
	else
	{
		if(_struct->fix_cmd[variables->i][variables->j + 1] == '?')
		{
			variables->c++;
			_struct->the_commande = ft_strjoin_v2(_struct->the_commande,
			ft_substr(_struct->fix_cmd[variables->i], variables->c, \
        	variables->j - variables->c));
			variables->j++;
			_struct->the_commande = ft_strjoin(_struct->the_commande,ft_itoa(_struct->exit_status));
			variables->c = variables->j;
		}
		else if(_struct->status == OUTSIDE && (_struct->fix_cmd[variables->i][variables->j + 1] == 34 || _struct->fix_cmd[variables->i][variables->j + 1] == 39))
			variables->c = variables->j;
		else if(_struct->fix_cmd[variables->i][variables->j + 1] != 34 && _struct->fix_cmd[variables->i][variables->j + 1] != 39)
		{
			variables->j++;
			variables->c = variables->j;
		}

	}
}

int	parccen_part(t_all *_struct, t_var *variables, char *splite)
{
	while (_struct->fix_cmd[variables->i])
	{
		variables->j = 0;
		variables->c = -1;
		_struct->status = OUTSIDE;
		while (_struct->fix_cmd[variables->i][variables->j])
		{
			quote_and_dqout(_struct, variables);
			pipe_and_rederaction_parceen(_struct, variables);
			if (_struct->fix_cmd[variables->i][variables->j] == '$'
				&& _struct->fix_cmd[variables->i][variables->j + 1])
				variables_parceen_utils(_struct, variables);
			variables->j++;
		}
		if(_struct->status != OUTSIDE)
		{
			ft_putstr_fd("minishell: unexpected EOF while looking for matching\n", 2);
			return -1;
		}
		if (_struct->status == OUTSIDE)
		{
			variables->c++;
			_struct->the_commande = ft_strjoin_v2(_struct->the_commande, \
				ft_substr(_struct->fix_cmd[variables->i], variables->c, \
				variables->j - variables->c));
		}
		_struct->the_commande = ft_strjoin(_struct->the_commande, splite);
		free(_struct->fix_cmd[variables->i]);
		_struct->fix_cmd[variables->i] = 0;
		variables->i++;
	}
	return 1;
}


void	initialisaion(t_all *_struct, t_var *variables, int c_of_s)
{
	// int buckup = variables->j;
	_struct->each_cmd[variables->i].files[c_of_s].OUTPUT = 0;
	_struct->each_cmd[variables->i].files[c_of_s].APPEND = 0;
	_struct->each_cmd[variables->i].files[c_of_s].number_of_O = 0;
	_struct->each_cmd[variables->i].files[c_of_s].number_of_I = 0;
	_struct->each_cmd[variables->i].files[c_of_s].INPUT = 0;
	_struct->each_cmd[variables->i].files[c_of_s].HERDOC = 0;
	_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSO = 0;
	_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSI = 0;
}

int 	inistialisation_input(t_all *_struct, t_var *variables, int c_of_s,
		int var)
{
	if(_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSO)
	{
		printf("minishell : syntax error");
		return -1;
	}
	_struct->each_cmd[variables->i].files[c_of_s].files = \
    ft_substr(_struct->splite_pipe[variables->i],variables->j, var - variables->j);
	if(!*_struct->each_cmd[variables->i].files[c_of_s].files)
	{
		printf("minishell : syntax error\n");
		return -1;
	}
	if(ft_strchr(_struct->each_cmd[variables->i].files[c_of_s].files, 6) && \
	ft_strlen(_struct->each_cmd[variables->i].files[c_of_s].files) == 1)
		_struct->each_cmd[variables->i].files[c_of_s].files = ft_strdup("");
	if (_struct->each_cmd[variables->i].files[c_of_s].number_of_I == 1)
		_struct->each_cmd[variables->i].files[c_of_s].INPUT = 1;
	else if (_struct->each_cmd[variables->i].files[c_of_s].number_of_I == 2)
		_struct->each_cmd[variables->i].files[c_of_s].HERDOC = 1;
	return 0;
}
int		inistialisation_output(t_all *_struct, t_var *variables, int c_of_s,
		int var)
{
	if(_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSO)
	if(_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSI)
	{
		printf("minishell : syntax error\n");
		return -1;
	}
	_struct->each_cmd[variables->i].files[c_of_s].files = \
    ft_substr(_struct->splite_pipe[variables->i],variables->j, var - variables->j);
	if(!*_struct->each_cmd[variables->i].files[c_of_s].files)
	{
		printf("minishell : syntax error\n");
		return -1;
	}
	if(ft_strchr(_struct->each_cmd[variables->i].files[c_of_s].files, 6) && \
	ft_strlen(_struct->each_cmd[variables->i].files[c_of_s].files) == 1)
		_struct->each_cmd[variables->i].files[c_of_s].files = ft_strdup("");
	else if (_struct->each_cmd[variables->i].files[c_of_s].number_of_O == 2)
		_struct->each_cmd[variables->i].files[c_of_s].APPEND = 1;
	else if (_struct->each_cmd[variables->i].files[c_of_s].number_of_O == 1)
		_struct->each_cmd[variables->i].files[c_of_s].OUTPUT = 1;
	return 0;
}
int	rediraction_calculate_output(t_all *_struct, t_var *variables, int var, int c_of_s)
{
	while (_struct->splite_pipe[variables->i][variables->j]
		&& (_struct->splite_pipe[variables->i][variables->j] == 2
			|| _struct->splite_pipe[variables->i][variables->j] == 3
			|| _struct->splite_pipe[variables->i][variables->j] == 5))
	{
		if(_struct->splite_pipe[variables->i][variables->j] == 2)
				_struct->each_cmd[variables->i].files[c_of_s].number_of_O++;
		if(_struct->splite_pipe[variables->i][variables->j] == 5)
				_struct->each_cmd[variables->i].files[c_of_s].number_of_I++;
		if(_struct->each_cmd[variables->i].files[c_of_s].number_of_O \
		&& _struct->each_cmd[variables->i].files[c_of_s].number_of_I)
		{
			_struct->each_cmd[variables->i].files[c_of_s].number_of_O = 0;
			_struct->each_cmd[variables->i].files[c_of_s].number_of_I = 0;
			_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSO = 1;
			return 0;
		}
		variables->j++;
	}
	var = variables->j;
	while (_struct->splite_pipe[variables->i][var]
		&& _struct->splite_pipe[variables->i][var] != 2
		&& _struct->splite_pipe[variables->i][var] != 5
		&& _struct->splite_pipe[variables->i][var] != 3)
		var++;
	return (var);
}
int	rediraction_calculate_input(t_all *_struct, t_var *variables, int var, int c_of_s)
{
	while (_struct->splite_pipe[variables->i][variables->j]
		&& (_struct->splite_pipe[variables->i][variables->j] == 2
			|| _struct->splite_pipe[variables->i][variables->j] == 3
			|| _struct->splite_pipe[variables->i][variables->j] == 5))
	{
		if(_struct->splite_pipe[variables->i][variables->j] == 2)
				_struct->each_cmd[variables->i].files[c_of_s].number_of_O++;
		if(_struct->splite_pipe[variables->i][variables->j] == 5)
				_struct->each_cmd[variables->i].files[c_of_s].number_of_I++;
		if(_struct->each_cmd[variables->i].files[c_of_s].number_of_O \
		&& _struct->each_cmd[variables->i].files[c_of_s].number_of_I)
		{
			_struct->each_cmd[variables->i].files[c_of_s].number_of_O = 0;
			_struct->each_cmd[variables->i].files[c_of_s].number_of_I = 0;
			_struct->each_cmd[variables->i].files[c_of_s].ERROR_SYNTACSI = 1;
			return 0;
		}
		variables->j++;
	}
	var = variables->j;
	while (_struct->splite_pipe[variables->i][var]
		&& _struct->splite_pipe[variables->i][var] != 2
		&& _struct->splite_pipe[variables->i][var] != 5
		&& _struct->splite_pipe[variables->i][var] != 3)
		var++;
	return (var);
}
void	commande_and_args(t_all *_struct, t_var *variables, int var)
{
	var = variables->j;
	while (_struct->splite_pipe[variables->i][var]
		&& (_struct->splite_pipe[variables->i][var] != 2
			&& _struct->splite_pipe[variables->i][var] != 5))
		var++;
	_struct->the_commande = ft_strjoin_v2(_struct->the_commande,\
	            ft_substr(_struct->splite_pipe[variables->i],\
	            variables->j, var\
	            - variables->j));
	variables->j = var - 1;

}

void	if_rediraction_is_existe(t_all *_struct, t_var *variables, int var)
{
	if (ft_strchr(_struct->splite_pipe[variables->i], 2)
		|| ft_strchr(_struct->splite_pipe[variables->i], 5))
	{
		var = 0;
		while (_struct->splite_pipe[variables->i][variables->j])
		{
			if (_struct->splite_pipe[variables->i][variables->j] == 2
				|| _struct->splite_pipe[variables->i][variables->j] == 5)
			{
				while (_struct->splite_pipe[variables->i][variables->j] == 2)
					variables->j++;
				var++;
			}
			if(!_struct->splite_pipe[variables->i][variables->j])
				break;
			variables->j++;
		}
		_struct->each_cmd[variables->i].files = ft_calloc(sizeof(t_files),
				(var + 1));
	}
}

int	any_commde_parceen(t_all *_struct, t_var *variables, int var,
		int c_of_s)
{
	if (_struct->splite_pipe[variables->i][variables->j] == 2)
	{
		initialisaion(_struct, variables, c_of_s);
		var = rediraction_calculate_output(_struct, variables,  var, c_of_s);
		if(inistialisation_output(_struct, variables, c_of_s, var))
			return -1;
		c_of_s++;
		variables->j = var - 1;
	}
	else if (_struct->splite_pipe[variables->i][variables->j] == 5)
	{
		initialisaion(_struct, variables, c_of_s);
		var = rediraction_calculate_input(_struct, variables, var, c_of_s);
		if(inistialisation_input(_struct, variables, c_of_s, var))
			return -1;
		c_of_s++;
		variables->j = var - 1;
	}
	else if (_struct->splite_pipe[variables->i][variables->j] != 5
			&& _struct->splite_pipe[variables->i][variables->j] != 2)
		commande_and_args(_struct, variables, var);
	return c_of_s;
}

int	rederaction_parccen(t_all *_struct, t_var *variables)
{
	int	c_of_s;
	int	var;
	// int	k;

	c_of_s = 0;
	var = 0;
	while (_struct->splite_pipe[variables->i])
	{
		variables->j = 0;
		_struct->the_commande = ft_calloc(1, 1);
		if_rediraction_is_existe(_struct, variables, var);
		c_of_s = 0;
		variables->j = 0;
		while (_struct->splite_pipe[variables->i][variables->j])
		{
			c_of_s = any_commde_parceen(_struct, variables, var, c_of_s);
			if(c_of_s == -1)
				return -1;
			variables->j++;
		}
		_struct->each_cmd[variables->i].cmd = ft_split(_struct->the_commande,
				3);
		var = 0;
		while(_struct->each_cmd[variables->i].cmd[var])
		{
			if(ft_strchr(_struct->each_cmd[variables->i].cmd[var], 6) && \
			ft_strlen(_struct->each_cmd[variables->i].cmd[var]) == 1)
				_struct->each_cmd[variables->i].cmd[var] = ft_strdup("");
			var++;
		}
		// if(_struct->each_cmd[c_of_s].cmd && !*_struct->each_cmd[c_of_s].cmd && _struct->number_of_pipes > 1)
		// {
		// 	if(_struct->number_of_pipes > 2)
		// 		ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
		// 	else
		// 		ft_putstr_fd("syntax error : only pipe\n", 2);
		// 	return(-1);
		// }
		free(_struct->splite_pipe[variables->i]);
		free(_struct->the_commande);
		_struct->the_commande = 0;
		_struct->splite_pipe[variables->i] = 0;
		variables->i++;
	}
	free(_struct->splite_pipe);
	return 0;
}

int	fix_arg(t_all *_struct)
{
	t_var variables;
	variables.i = 0;
	variables.j = 0;
	variables.c = -1;
	char splite[2];
	splite[0] = 3;
	splite[1] = '\0';
	_struct->number_of_pipes = 1;
	_struct->the_commande = 0;
	_struct->the_commande = ft_calloc(1, 1);
	if(parccen_part(_struct, &variables, splite) == -1)
		return 2;
	free(_struct->fix_cmd);
	_struct->splite_pipe = ft_split(_struct->the_commande, 4);
	// int i = 0;
	// while(_struct->splite_pipe[i])
	// {
	// 	printf("[%s]\n", _struct->splite_pipe[i]);
	// 	i++;
	// }
	free(_struct->the_commande);
	_struct->the_commande = 0;
	variables.i = 0;
	_struct->each_cmd = ft_calloc(sizeof(t_each_command),\
		_struct->number_of_pipes + 1);
	if(rederaction_parccen(_struct, &variables))
		return 258;
	return 0;
}