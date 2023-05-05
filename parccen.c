/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/05 21:15:24 by nouakhro         ###   ########.fr       */
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
	if ((_struct->fix_cmd[variables->index_i][variables->index_j] == 34)
		&& _struct->status != IN_COTE)
	{
		_struct->fix_cmd[variables->index_i][variables->index_j] = 8;
		if (_struct->fix_cmd[variables->index_i][variables->index_j] == 8
			&& _struct->status == IN_DCOTE)
			_struct->status = OUTSIDE;
		else
			_struct->status = IN_DCOTE;
	}
	if ((_struct->fix_cmd[variables->index_i][variables->index_j] == 39)
		&& _struct->status != IN_DCOTE)
	{
		_struct->fix_cmd[variables->index_i][variables->index_j] = 6;
		if (_struct->fix_cmd[variables->index_i][variables->index_j] == 6
			&& _struct->status == IN_COTE)
			_struct->status = OUTSIDE;
		else
			_struct->status = IN_COTE;
	}
	return (variables->start);
}

void	pipe_and_rederaction_parceen(t_all *_struct, t_var *variables)
{
	if (_struct->fix_cmd[variables->index_i][variables->index_j] == '|'
		&& _struct->status == OUTSIDE)
	{
		_struct->fix_cmd[variables->index_i][variables->index_j] = 4;
		_struct->number_of_pipes++;
	}
	if (_struct->fix_cmd[variables->index_i][variables->index_j] == '>'
		&& _struct->status == OUTSIDE)
	{
		_struct->fix_cmd[variables->index_i][variables->index_j] = 2;
		_struct->if_rediraction = 1;
	}
	if (_struct->fix_cmd[variables->index_i][variables->index_j] == '<'
		&& _struct->status == OUTSIDE)
	{
		_struct->fix_cmd[variables->index_i][variables->index_j] = 5;
		_struct->if_rediraction = 1;
	}
}

char	*my_getenv(t_list *head, char *var, int trim)
{
	int		j;
	int		i;
	char	*expande_variable;

	j = 0;
	(void)var;
	i = 0;
	expande_variable = ft_calloc(1, 1);
	while (head != NULL)
	{
		if (*(char *)head->content == var[0])
		{
			j = 0;
			while (((char *)head->content)[j] == var[j] ||
					((char *)head->content)[j] == '=')
			{
				if (((char *)head->content)[j] == '=' && !var[j])
				{
					free(expande_variable);
					expande_variable = ft_substr(head->content, j + 1,
							ft_strlen(head->content + (j + 1)));
					i = 0;
					if (trim == 1)
					{
						while (expande_variable[i])
						{
							if (expande_variable[i] == ' ')
								expande_variable[i] = 3;
							i++;
						}
					}
					return (expande_variable);
				}
				j++;
			}
		}
		head = head->next;
	}
	return (expande_variable);
}

char	*variables_parceen(t_all *_struct, t_var *variables,
		char *whotout_expande, char *my_string)
{
	int		var;
	char	*variable;
	char	*str;

	var = variables->index_j + 1;
	while (whotout_expande[var] && (ft_isalpha(whotout_expande[var])
			|| ft_isdigit(whotout_expande[var])))
		var++;
	if (_struct->status == IN_DCOTE || _struct->status == OUTSIDE)
	{
		if (ft_isdigit(whotout_expande[variables->index_j + 1])
			&& whotout_expande[variables->index_j + 1] != '_')
		{
			variables->index_j++;
			variable =
				ft_substr(whotout_expande, variables->index_j + 1, (var
							- (variables->index_j + 1)));
			my_string = ft_strjoin_v2(my_string, variable);
			variables->index_j = var - 1;
		}
		else if (ft_isalpha(whotout_expande[variables->index_j + 1])
				|| whotout_expande[variables->index_j + 1] == '_')
		{
			variable = ft_substr(whotout_expande, variables->index_j + 1, (var
						- (variables->index_j + 1)));
			if (_struct->status == IN_DCOTE)
				variable = my_getenv(_struct->list, variable, 0);
			else
				variable = my_getenv(_struct->list, variable, 1);
			if (variable)
			{
				my_string = ft_strjoin(my_string, variable);
				if (_struct->ambiguous == 1)
				{
					str = ft_strtrim(my_string, "\003\000");
					if (!str || (ft_strlen(str) == 0
							&& ((whotout_expande[variables->index_j - 1] == 3
									&& (whotout_expande[var] == 3
										|| whotout_expande[var] == 0))
								|| ft_strchr(variable, 3))))
						_struct->error_ambiguous = 1;
					free(str);
				}
				free(variable);
			}
			variables->index_j = var - 1;
		}
	}
	if (_struct->status == IN_COTE)
	{
		variable = ft_substr(whotout_expande, variables->index_j, (var
					- variables->index_j));
		my_string = ft_strjoin_v2(my_string,
									variable);
		variables->index_j = var - 1;
	}
	return (my_string);
}

char	*variables_parceen_rederaction(char *whotout_expande, char *my_string,
		t_all *_struct, t_var *variables)
{
	if (ft_isalnum(whotout_expande[variables->index_j + 1]))
	{
		if (whotout_expande[variables->index_j + 1])
		{
			variables->start++;
			my_string = variables_parceen(_struct, variables, whotout_expande,
					my_string);
			variables->start = variables->index_j;
		}
	}
	else
	{
		if (whotout_expande[variables->index_j + 1] == '?')
		{
			if (_struct->status != IN_COTE)
			{
				variables->index_j++;
				my_string = ft_strjoin(my_string,
										ft_itoa(_struct->exit_status));
				variables->start = variables->index_j;
			}
		}
		else if ((whotout_expande[variables->index_j + 1] == 34
					|| whotout_expande[variables->index_j + 1] == 39)
				&& _struct->status == OUTSIDE)
			variables->start = variables->index_j;
		else if (!ft_isalnum(whotout_expande[variables->index_j + 1])
				&& whotout_expande[variables->index_j + 1] != '$')
		{
			variables->index_j++;
			variables->start = variables->index_j;
		}
		else
		{
			variables->index_j++;
			variables->start = variables->index_j - 1;
		}
	}
	return (my_string);
}

char	*variables_parceen_utils(char *whotout_expande, char *my_string,
		t_all *_struct, t_var *variables)
{
	if (ft_isalnum(whotout_expande[variables->index_j + 1]))
	{
		if (whotout_expande[variables->index_j + 1])
		{
			variables->start++;
			my_string = variables_parceen(_struct, variables, whotout_expande,
					my_string);
			variables->start = variables->index_j;
		}
	}
	else
	{
		if (whotout_expande[variables->index_j + 1] == '?')
		{
			if (_struct->status != IN_COTE)
			{
				variables->index_j++;
				my_string = ft_strjoin_v2(my_string,
											ft_itoa(_struct->exit_status));
				variables->start = variables->index_j;
			}
			else
				variables->start = variables->index_j - 1;
		}
		else if (_struct->status != OUTSIDE
				&& (whotout_expande[variables->index_j + 1] == 8
					|| whotout_expande[variables->index_j + 1] == 6))
			variables->start = variables->index_j - 1;
		else if (!ft_isalnum(whotout_expande[variables->index_j + 1])
				&& whotout_expande[variables->index_j + 1] != '$'
				&& whotout_expande[variables->index_j + 1] != 8
				&& whotout_expande[variables->index_j + 1] != 6)
		{
			variables->index_j++;
			variables->start = variables->index_j;
		}
		else if (whotout_expande[variables->index_j + 1] == '$')
		{
			variables->index_j++;
			variables->start = variables->index_j - 1;
		}
	}
	return (my_string);
}

int change_qouts_and_pipe_and_rederaction(t_all *_struct, t_var *variables)
{
	while (_struct->fix_cmd[variables->index_i][variables->index_j])
	{
		quote_and_dqout(_struct, variables);
		pipe_and_rederaction_parceen(_struct, variables);
		if (_struct->fix_cmd[variables->index_i][variables->index_j] == 4
			&&
			((variables->index_j == 0 && variables->index_i == 0)
					|| (variables->index_j - 1 >= 0
						&& _struct->fix_cmd[variables->index_i][variables->index_j
						- 1] == 4)
					|| (_struct->fix_cmd[variables->index_i][variables->index_j
						+ 1] == 0 && _struct->fix_cmd[variables->index_i
						+ 1] == 0)))
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			while (_struct->fix_cmd[variables->index_i])
			{
				free(_struct->fix_cmd[variables->index_i]);
				variables->index_i++;
			}
			free(_struct->fix_cmd);
			if (_struct->the_commande)
				free(_struct->the_commande);
			return (258);
		}
		variables->index_j++;
	}
	return 0;
}

int	parccen_part(t_all *_struct, t_var *variables)
{
	while (_struct->fix_cmd[variables->index_i])
	{
		variables->index_j = 0;
		_struct->status = OUTSIDE;
		if(change_qouts_and_pipe_and_rederaction(_struct,variables) == 258)
			return 258;
		// while (_struct->fix_cmd[variables->index_i][variables->index_j])
		// {
		// 	quote_and_dqout(_struct, variables);
		// 	pipe_and_rederaction_parceen(_struct, variables);
		// 	if (_struct->fix_cmd[variables->index_i][variables->index_j] == 4
		// 		&&
		// 		((variables->index_j == 0 && variables->index_i == 0)
		// 				|| (variables->index_j - 1 >= 0
		// 					&& _struct->fix_cmd[variables->index_i][variables->index_j
		// 					- 1] == 4)
		// 				|| (_struct->fix_cmd[variables->index_i][variables->index_j
		// 					+ 1] == 0 && _struct->fix_cmd[variables->index_i
		// 					+ 1] == 0)))
		// 	{
		// 		ft_putstr_fd("minishell: syntax error\n", 2);
		// 		while (_struct->fix_cmd[variables->index_i])
		// 		{
		// 			free(_struct->fix_cmd[variables->index_i]);
		// 			variables->index_i++;
		// 		}
		// 		free(_struct->fix_cmd);
		// 		if (_struct->the_commande)
		// 			free(_struct->the_commande);
		// 		return (258);
		// 	}
		// 	variables->index_j++;
		// }
		if (_struct->status != OUTSIDE)
		{
			ft_putstr_fd("minishell: unexpected EOF while looking for matching\n",
							2);
			return (-1);
		}
		_struct->the_commande = ft_strjoin_v2(_struct->the_commande,
												_struct->fix_cmd[variables->index_i]);
		if (_struct->fix_cmd[variables->index_i + 1])
			_struct->the_commande = ft_strjoin(_struct->the_commande,
					"\003\000");
		_struct->fix_cmd[variables->index_i] = 0;
		variables->index_i++;
	}
	return (1);
}

void	initialisaion(t_all *_struct, t_var *variables, int c_of_s)
{
	_struct->each_cmd[variables->index_i].files[c_of_s].OUTPUT = 0;
	_struct->each_cmd[variables->index_i].files[c_of_s].APPEND = 0;
	_struct->each_cmd[variables->index_i].files[c_of_s].number_of_O = 0;
	_struct->each_cmd[variables->index_i].files[c_of_s].number_of_I = 0;
	_struct->each_cmd[variables->index_i].files[c_of_s].INPUT = 0;
	_struct->each_cmd[variables->index_i].files[c_of_s].HERDOC = 0;
	_struct->each_cmd[variables->index_i].files[c_of_s].ERROR_SYNTACSO = 0;
	_struct->each_cmd[variables->index_i].files[c_of_s].ERROR_SYNTACSI = 0;
	_struct->each_cmd[variables->index_i].files[c_of_s].HERDOC_OPTION = 0;
	_struct->each_cmd[variables->index_i].files[c_of_s].ambiguous = 0;
}

char *what_insied_herdoc(t_all *_struct, t_var *indes, char *buffer, char *herdoc)
{
	char	*buffer_tmp;

	if ((buffer[indes->index_i] == '$' && buffer[indes->index_i + 1] && buffer[indes->index_i + 1] != ' '))
	{
		herdoc = ft_strjoin_v2(herdoc, ft_substr(buffer, indes->start, indes->index_i - indes->start));
		indes->index_i++;
		if (buffer[indes->index_i] == '?')
		{
			herdoc = ft_strjoin_v2(herdoc, ft_itoa(_struct->exit_status));
			indes->index_i++;
			indes->start = indes->index_i;
		}
		else
		{
			indes->start = indes->index_i;
			while (ft_isalnum(buffer[indes->index_i]))
				indes->index_i++;
			buffer_tmp = ft_substr(buffer, indes->start, indes->index_i - indes->start);
			herdoc = ft_strjoin_v2(herdoc, my_getenv(_struct->list, buffer_tmp, 0));
			free(buffer_tmp);
			indes->start = indes->index_i;
		}
		indes->index_i--;
	}
	return herdoc;
}

void parrcing_of_insied_herdoc(t_all *_struct, t_var *variables, int c_of_s, int c)
{
	int		fd_by_pipe[2];
	char	*buffer;
	char	*herdoc;
	t_var indes;

	buffer = 0;
	herdoc = ft_strdup("");
	indes.index_i = 0;
	indes.start = 0;
	pipe(fd_by_pipe);
	while (1)
	{
		buffer = readline("> ");
		if (!buffer)
			break ;
		if (!ft_strncmp(buffer, _struct->each_cmd[variables->index_i].files[c_of_s].files, ft_strlen(buffer) + 1))
			break ;
		if (ft_strchr(buffer, '$')
			&& _struct->each_cmd[c_of_s].files[c_of_s].HERDOC_OPTION == 0)
		{
			indes.index_i = -1;
			c = 0;
			while (buffer[++indes.index_i])
			{
				herdoc = what_insied_herdoc(_struct, &indes, buffer, herdoc);
				if (!buffer[indes.index_i])
					break ;
			}
			herdoc = ft_strjoin_v2(herdoc, ft_substr(buffer, c, indes.index_i - c));
		}
		else
			herdoc = ft_strjoin(herdoc, buffer);
		herdoc = ft_strjoin(herdoc, "\n");
	}
	ft_putstr_fd(herdoc, fd_by_pipe[1]);
	close(fd_by_pipe[1]);
	free(herdoc);
	_struct->fils_descreprot = fd_by_pipe[0];
}

int	inistialisation_input(t_all *_struct, t_var *variables, int c_of_s)
{
	char	**str;
	int		checher;

	checher = 0;
	if (_struct->each_cmd[variables->index_i].files[c_of_s].number_of_I > 2)
		checher = 1;
	if (_struct->each_cmd[variables->index_i].files[c_of_s].number_of_O
		&& _struct->each_cmd[variables->index_i].files[c_of_s].number_of_I)
		checher = 1;
	if (!_struct->tmp_cmd[variables->index_j])
		checher = 1;
	if (checher == 1)
	{
		checher = fork();
		if (checher == 0)
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			exit(1);
		}
		wait(&checher);
		return (-1);
	}
	variables->start = variables->index_j - 1;
	_struct->each_cmd[variables->index_i].files[c_of_s].files = ft_calloc(1,
			1);
	if (_struct->each_cmd[variables->index_i].files[c_of_s].number_of_I == 2)
		_struct->each_cmd[variables->index_i].files[c_of_s].HERDOC = 1;
	_struct->ambiguous = 1;
	_struct->error_ambiguous = 0;
	qouts(_struct, variables, c_of_s);
	str = ft_split(_struct->each_cmd[variables->index_i].files[c_of_s].files,
			3);
	checher = 0;
	if (str[checher])
	{
		free(_struct->each_cmd[variables->index_i].files[c_of_s].files);
		_struct->each_cmd[variables->index_i].files[c_of_s].files = 0;
	}
	while (str[checher])
	{
		_struct->each_cmd[variables->index_i].files[c_of_s].files = ft_strdup(str[checher]);
		free(str[checher]);
		checher++;
	}
	free(str);
	if ((_struct->error_ambiguous == 1 && checher == 0) || checher > 1)
		_struct->each_cmd[variables->index_i].files[c_of_s].ambiguous = 1;
	if (_struct->each_cmd[variables->index_i].files[c_of_s].number_of_I == 1)
		_struct->each_cmd[variables->index_i].files[c_of_s].INPUT = 1;
	else if (_struct->each_cmd[variables->index_i].files[c_of_s].number_of_I == 2)
		parrcing_of_insied_herdoc(_struct, variables, c_of_s, 0);
	variables->index_j = variables->end - 1;
	return (0);
}

void syntax_error(t_all *_struct, t_var *variables)
{
	int i;
	i = fork();
	if (i == 0)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		exit(1);
	}
	wait(&i);
	i = 0;
	while (_struct->each_cmd[i].files)
	{
		free(_struct->each_cmd[i].files);
		i++;
	}
	free(_struct->each_cmd);
	free(_struct->tmp_cmd);
	free(_struct->the_commande);
	while (_struct->splite_pipe[variables->index_i])
	{
		free(_struct->splite_pipe[variables->index_i]);
		variables->index_i++;
	}
	free(_struct->splite_pipe);
}

int remove_qouts_and_expande_variables_in_output(t_all *_struct, t_var *variables, int c_of_s, int if_error)
{
	char **str;

	if (_struct->each_cmd[variables->index_i].files[c_of_s].number_of_O == 2)
		_struct->each_cmd[variables->index_i].files[c_of_s].APPEND = 1;
	else if (_struct->each_cmd[variables->index_i].files[c_of_s].number_of_O == 1)
		_struct->each_cmd[variables->index_i].files[c_of_s].OUTPUT = 1;
	variables->start = variables->index_j - 1;
	_struct->each_cmd[variables->index_i].files[c_of_s].files = ft_calloc(1, 1);
	_struct->ambiguous = 1;
	_struct->error_ambiguous = 0;
	qouts(_struct, variables, c_of_s);
	str = ft_split(_struct->each_cmd[variables->index_i].files[c_of_s].files, 3);
	if (str[if_error])
	{
		free(_struct->each_cmd[variables->index_i].files[c_of_s].files);
		_struct->each_cmd[variables->index_i].files[c_of_s].files = 0;
	}
	while (str[if_error])
	{
		_struct->each_cmd[variables->index_i].files[c_of_s].files = ft_strdup(str[if_error]);
		free(str[if_error]);
		if_error++;
	}
	free(str);
	return if_error;
}

int	inistialisation_output(t_all *_struct, t_var *variables, int c_of_s)
{
	int		if_error;

	if_error = 0;
	if (_struct->each_cmd[variables->index_i].files[c_of_s].number_of_O > 2)
		if_error = 1;
	if (_struct->each_cmd[variables->index_i].files[c_of_s].number_of_O
		&& _struct->each_cmd[variables->index_i].files[c_of_s].number_of_I)
		if_error = 1;
	if (!_struct->tmp_cmd[variables->index_j])
		if_error = 1;
	if (if_error == 1)
	{
		syntax_error(_struct, variables);
		return (-1);
	}
	if_error = remove_qouts_and_expande_variables_in_output(_struct, variables, c_of_s, 0);
	if ((_struct->error_ambiguous == 1 && if_error == 0) || if_error > 1)
		_struct->each_cmd[variables->index_i].files[c_of_s].ambiguous = 1;
	variables->index_j = variables->end - 1;
	return (0);
}

int how_many_rederaction_output(t_all *_struct, t_var *variables, int c_of_s)
{
	if (_struct->tmp_cmd[variables->index_j] == 2)
	{
		while (_struct->tmp_cmd[variables->index_j] == 2)
		{
			_struct->each_cmd[variables->index_i].files[c_of_s].number_of_O++;
			variables->index_j++;
		}
	}
	if (_struct->tmp_cmd[variables->index_j] == 5)
	{
		while (_struct->tmp_cmd[variables->index_j] == 5)
		{
			_struct->each_cmd[variables->index_i].files[c_of_s].number_of_I++;
			variables->index_j++;
		}
	}
	if (_struct->tmp_cmd[variables->index_j] == 0
	|| (_struct->tmp_cmd[variables->index_j] != 5
		&& _struct->tmp_cmd[variables->index_j] != 2)
	|| (_struct->each_cmd[variables->index_i].files[c_of_s].number_of_O
		&& _struct->each_cmd[variables->index_i].files[c_of_s].number_of_I))
		return 1;
	return 0;
}

void	rediraction_calculate_output(t_all *_struct, t_var *variables, int c_of_s)
{
	while (_struct->tmp_cmd[variables->index_j]
		&& (_struct->tmp_cmd[variables->index_j] == 2
			|| _struct->tmp_cmd[variables->index_j] == 5))
	{
		if(how_many_rederaction_output(_struct, variables, c_of_s))
			break;
		variables->index_j++;
	}
	while (_struct->tmp_cmd[variables->index_j]
		&& _struct->tmp_cmd[variables->index_j] == 3)
		variables->index_j++;
	variables->end = variables->index_j;
	while (_struct->tmp_cmd[variables->end]
		&& _struct->tmp_cmd[variables->end] != 2
		&& _struct->tmp_cmd[variables->end] != 5
		&& _struct->tmp_cmd[variables->end] != 3)
	{
		if (_struct->tmp_cmd[variables->end] == 8
			|| _struct->tmp_cmd[variables->end] == 6)
			_struct->each_cmd[variables->index_i].files[c_of_s].HERDOC_OPTION = 1;
		variables->end++;
	}
	// return (variables->end);
}

int how_many_rederaction_input(t_all *_struct, t_var *variables, int c_of_s)
{
	if (_struct->tmp_cmd[variables->index_j] == 5)
	{
		while (_struct->tmp_cmd[variables->index_j] == 5)
		{
			_struct->each_cmd[variables->index_i].files[c_of_s].number_of_I++;
			variables->index_j++;
		}
	}
	if (_struct->tmp_cmd[variables->index_j] == 2)
	{
		while (_struct->tmp_cmd[variables->index_j] == 2)
		{
			_struct->each_cmd[variables->index_i].files[c_of_s].number_of_O++;
			variables->index_j++;
		}
	}
	if (_struct->tmp_cmd[variables->index_j] == 0
		|| (_struct->tmp_cmd[variables->index_j] != 5
			&& _struct->tmp_cmd[variables->index_j] != 2)
		|| (_struct->each_cmd[variables->index_i].files[c_of_s].number_of_O
			&& _struct->each_cmd[variables->index_i].files[c_of_s].number_of_I))
		return 1;
	return 0;
}

void	rediraction_calculate_input(t_all *_struct, t_var *variables,
		int c_of_s)
{
	while (_struct->tmp_cmd[variables->index_j]
		&& (_struct->tmp_cmd[variables->index_j] == 2
			|| _struct->tmp_cmd[variables->index_j] == 5))
	{
	if(how_many_rederaction_input(_struct, variables, c_of_s))
			break;
		variables->index_j++;
	}
	while (_struct->tmp_cmd[variables->index_j]
		&& _struct->tmp_cmd[variables->index_j] == 3)
		variables->index_j++;
	variables->end = variables->index_j;
	while (_struct->tmp_cmd[variables->end]
		&& _struct->tmp_cmd[variables->end] != 2
		&& _struct->tmp_cmd[variables->end] != 5
		&& _struct->tmp_cmd[variables->end] != 3)
	{
		if (_struct->tmp_cmd[variables->end] == 8
			|| _struct->tmp_cmd[variables->end] == 6)
			_struct->each_cmd[variables->index_i].files[c_of_s].HERDOC_OPTION = 1;
		variables->end++;
	}
	// return (variables->end);
}
void	commande_and_args(t_all *_struct, t_var *variables)
{
	variables->end = variables->index_j;
	variables->start = variables->index_j - 1;
	_struct->ambiguous = 2;
	while (_struct->tmp_cmd[variables->end]
		&& (_struct->tmp_cmd[variables->end] != 2
			&& _struct->tmp_cmd[variables->end] != 5))
		variables->end++;
	while (variables->index_j < variables->end)
	{
		if (_struct->tmp_cmd[variables->index_j] == 8
			&& _struct->status != IN_COTE)
		{
			if (_struct->status == IN_DCOTE)
				_struct->status = OUTSIDE;
			else
				_struct->status = IN_DCOTE;
		}
		else if (_struct->tmp_cmd[variables->index_j] == 6
				&& _struct->status != IN_DCOTE)
		{
			if (_struct->status == IN_COTE)
				_struct->status = OUTSIDE;
			else
				_struct->status = IN_COTE;
		}
		else if (_struct->tmp_cmd[variables->index_j] == '$'
				&& _struct->tmp_cmd[variables->index_j + 1]
				&& _struct->tmp_cmd[variables->index_j + 1] != ' '
				&& _struct->tmp_cmd[variables->index_j + 1] != 3)
		{
			variables->start++;
			_struct->the_commande = ft_strjoin_v2(_struct->the_commande,
													ft_substr(_struct->tmp_cmd,
																variables->start,
																variables->index_j
																	- variables->start));
			variables->start = variables->index_j;
			if (_struct->tmp_cmd[variables->index_j + 1])
			{
				_struct->parccer = 1;
				_struct->the_commande = variables_parceen_utils(_struct->tmp_cmd,
																	_struct->the_commande,
																	_struct,
																	variables);
			}
		}
		variables->index_j++;
	}
	variables->start++;
	_struct->the_commande = ft_strjoin_v2(_struct->the_commande,
											ft_substr(_struct->tmp_cmd,
													variables->start,
													variables->index_j
													- variables->start));
	variables->index_j = variables->end - 1;
}

void	if_rediraction_is_existe(t_all *_struct, t_var *variables)
{
	if (ft_strchr(_struct->tmp_cmd, 2)
		|| ft_strchr(_struct->splite_pipe[variables->index_i], 5))
	{
		variables->end = 0;
		while (_struct->tmp_cmd[variables->index_j])
		{
			if (_struct->tmp_cmd[variables->index_j] == 2
				|| _struct->tmp_cmd[variables->index_j] == 5)
			{
				while (_struct->tmp_cmd[variables->index_j] == 2)
					variables->index_j++;
				variables->end++;
			}
			if (!_struct->tmp_cmd[variables->index_j])
				break ;
			variables->index_j++;
		}
		_struct->each_cmd[variables->index_i].files = ft_calloc(sizeof(t_files),
		(variables->end + 1));
	}
}

int	commande_and_rederaction_parceen(t_all *_struct, t_var *variables, int c_of_s)
{
	int	i;

	if (_struct->tmp_cmd[variables->index_j] && \
	_struct->tmp_cmd[variables->index_j] == 2)
	{
		initialisaion(_struct, variables, c_of_s);
		rediraction_calculate_output(_struct, variables, c_of_s);
		i = inistialisation_output(_struct, variables, c_of_s);
		if(i != 0)
			return i;
		c_of_s++;
	}
	else if (_struct->tmp_cmd[variables->index_j]
			&& _struct->tmp_cmd[variables->index_j] == 5)
	{
		initialisaion(_struct, variables, c_of_s);
		rediraction_calculate_input(_struct, variables, c_of_s);
		i = inistialisation_input(_struct, variables, c_of_s);
		if(i != 0)
			return i;
		c_of_s++;
	}
	else
		commande_and_args(_struct, variables);
	return (c_of_s);
}

void	qouts(t_all *_struct, t_var *variables, int c_of_s)
{
	while (variables->index_j < variables->end)
	{
		if (_struct->tmp_cmd[variables->index_j] == 8
			&& _struct->status != IN_COTE)
		{
			if (_struct->status == IN_DCOTE)
			{
				_struct->each_cmd[variables->index_i].files[c_of_s].files =
					ft_strjoin(_struct->each_cmd[variables->index_i].files[c_of_s].files,
								"");
				_struct->status = OUTSIDE;
			}
			else
				_struct->status = IN_DCOTE;
			variables->start++;
			_struct->each_cmd[variables->index_i].files[c_of_s].files =
				ft_strjoin_v2(_struct->each_cmd[variables->index_i].files[c_of_s].files,
								ft_substr(_struct->tmp_cmd, variables->start,
										variables->index_j - variables->start));
			variables->start = variables->index_j;
		}
		else if (_struct->tmp_cmd[variables->index_j] == 6
				&& _struct->status != IN_DCOTE)
		{
			if (_struct->status == IN_COTE)
			{
				_struct->status = OUTSIDE;
				_struct->each_cmd[variables->index_i].files[c_of_s].files =
					ft_strjoin(_struct->each_cmd[variables->index_i].files[c_of_s].files,
								"");
			}
			else
				_struct->status = IN_COTE;
			variables->start++;
			_struct->each_cmd[variables->index_i].files[c_of_s].files =
				ft_strjoin_v2(_struct->each_cmd[variables->index_i].files[c_of_s].files,
								ft_substr(_struct->tmp_cmd, variables->start,
										variables->index_j - variables->start));
			variables->start = variables->index_j;
		}
		else if (_struct->tmp_cmd[variables->index_j] == '$'
				&& _struct->tmp_cmd[variables->index_j + 1]
				&& _struct->tmp_cmd[variables->index_j + 1] != ' '
				&& _struct->tmp_cmd[variables->index_j + 1] != 3
				&& _struct->each_cmd[variables->index_i].files[c_of_s].HERDOC == 0)
		{
			variables->start++;
			_struct->each_cmd[variables->index_i].files[c_of_s].files = ft_strjoin_v2(_struct->each_cmd[variables->index_i].files[c_of_s].files,
																						ft_substr(_struct->tmp_cmd,
																									variables->start,
																									variables->index_j
																										- variables->start));
			variables->start = variables->index_j;
			if (_struct->tmp_cmd[variables->index_j + 1])
				_struct->each_cmd[variables->index_i].files[c_of_s].files = variables_parceen_utils(_struct->tmp_cmd,
																										_struct->each_cmd[variables->index_i].files[c_of_s].files,
																										_struct,
																										variables);
		}
		variables->index_j++;
	}
	variables->start++;
	_struct->each_cmd[variables->index_i].files[c_of_s].files =
		ft_strjoin_v2(_struct->each_cmd[variables->index_i].files[c_of_s].files,
						ft_substr(_struct->tmp_cmd, variables->start,
								variables->index_j - variables->start));
}

void	qouts_comnde(t_all *_struct, t_var *variables)
{
	int	cas;

	_struct->each_cmd[variables->index_i].cmd = ft_split(_struct->the_commande,
															3);
	free(_struct->tmp_cmd);
	_struct->tmp_cmd = 0;
	variables->end = 0;
	cas = 0;
	while (_struct->each_cmd[variables->index_i].cmd[variables->end])
	{
		variables->index_j = 0;
		variables->start = -1;
		_struct->tmp_cmd = ft_calloc(1, 1);
		while (_struct->each_cmd[variables->index_i].cmd[variables->end][variables->index_j])
		{
			if (_struct->each_cmd[variables->index_i].cmd[variables->end][variables->index_j] == 8
				&& _struct->status != IN_COTE)
			{
				if (_struct->status == IN_DCOTE)
				{
					_struct->tmp_cmd = ft_strjoin(_struct->tmp_cmd, "");
					_struct->status = OUTSIDE;
				}
				else
					_struct->status = IN_DCOTE;
				variables->start++;
				_struct->tmp_cmd = ft_strjoin_v2(_struct->tmp_cmd,
													ft_substr(_struct->each_cmd[variables->index_i].cmd[variables->end],
																variables->start,
																variables->index_j
																	- variables->start));
				variables->start = variables->index_j;
			}
			else if (_struct->each_cmd[variables->index_i].cmd[variables->end][variables->index_j] == 6
					&& _struct->status != IN_DCOTE)
			{
				if (_struct->status == IN_COTE)
				{
					_struct->status = OUTSIDE;
					_struct->tmp_cmd = ft_strjoin(_struct->tmp_cmd, "");
				}
				else
					_struct->status = IN_COTE;
				variables->start++;
				_struct->tmp_cmd = ft_strjoin_v2(_struct->tmp_cmd,
													ft_substr(_struct->each_cmd[variables->index_i].cmd[variables->end],
																variables->start,
																variables->index_j
																	- variables->start));
				variables->start = variables->index_j;
			}
			variables->index_j++;
		}
		variables->start++;
		_struct->tmp_cmd = ft_strjoin_v2(_struct->tmp_cmd,
											ft_substr(_struct->each_cmd[variables->index_i].cmd[variables->end],
														variables->start,
														variables->index_j
															- variables->start));
		free(_struct->each_cmd[variables->index_i].cmd[variables->end]);
		_struct->each_cmd[variables->index_i].cmd[variables->end] = 0;
		if (!(ft_strchr(_struct->tmp_cmd, 7) &&
				ft_strlen(_struct->tmp_cmd) == 1))
		{
			_struct->each_cmd[variables->index_i].cmd[cas] = ft_strdup(_struct->tmp_cmd);
			cas++;
		}
		free(_struct->tmp_cmd);
		_struct->tmp_cmd = 0;
		variables->end++;
	}
}

int	partition_part(t_all *_struct, t_var *variables)
{
	int	c_of_s;

	c_of_s = 0;
	variables->end = 0;
	variables->index_i = 0;
	_struct->fils_descreprot = 0;
	while (_struct->splite_pipe[variables->index_i])
	{
		_struct->status = OUTSIDE;
		_struct->tmp_cmd = ft_strdup(_struct->splite_pipe[variables->index_i]);
		variables->index_j = 0;
		_struct->the_commande = ft_calloc(1, 1);
		if_rediraction_is_existe(_struct, variables);
		c_of_s = 0;
		variables->index_j = 0;
		while (_struct->tmp_cmd[variables->index_j])
		{
			_struct->parccer = 0;
			c_of_s = commande_and_rederaction_parceen(_struct, variables, c_of_s);
			if (c_of_s == -1)
				return (-1);
			if (c_of_s == -2)
				return (-2);
			variables->index_j++;
		}
		qouts_comnde(_struct, variables);
		free(_struct->splite_pipe[variables->index_i]);
		_struct->splite_pipe[variables->index_i] = 0;
		free(_struct->the_commande);
		_struct->the_commande = 0;
		variables->index_i++;
	}
	free(_struct->splite_pipe);
	return (0);
}

int	fix_arg(t_all *_struct)
{
	t_var variables;
	variables.index_i = 0;
	variables.index_j = 0;
	variables.start = -1;
	_struct->number_of_pipes = 1;
	_struct->the_commande = 0;
	_struct->the_commande = ft_calloc(1, 1);
	variables.index_i = parccen_part(_struct, &variables);
	if (variables.index_i == -1)
		return (2);
	if (variables.index_i == 258)
		return (258);
	free(_struct->fix_cmd);
	_struct->splite_pipe = ft_split(_struct->the_commande, 4);
	free(_struct->the_commande);
	_struct->the_commande = 0;
	variables.index_i = 0;
	_struct->each_cmd = ft_calloc(sizeof(t_each_command),
			_struct->number_of_pipes + 1);
	variables.index_i = partition_part(_struct, &variables);
	if (variables.index_i == -1)
		return (258);
	if (variables.index_i == -2)
		return (1);
	return (0);
}