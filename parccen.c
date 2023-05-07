/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/07 14:12:38 by nouakhro         ###   ########.fr       */
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
	i = -1;
	b = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!b)
		return (b);
	j = 0;
	while (s1[++i])
		b[i] = s1[i];
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

int	quote_and_dquote(t_var *variables)
{
	if ((g_struct.fix_cmd[variables->index_i][variables->index_j] == 34)
		&& g_struct.status != IN_COTE)
	{
		g_struct.fix_cmd[variables->index_i][variables->index_j] = 8;
		if (g_struct.fix_cmd[variables->index_i][variables->index_j] == 8
			&& g_struct.status == IN_DCOTE)
			g_struct.status = OUTSIDE;
		else
			g_struct.status = IN_DCOTE;
	}
	if ((g_struct.fix_cmd[variables->index_i][variables->index_j] == 39)
		&& g_struct.status != IN_DCOTE)
	{
		g_struct.fix_cmd[variables->index_i][variables->index_j] = 6;
		if (g_struct.fix_cmd[variables->index_i][variables->index_j] == 6
			&& g_struct.status == IN_COTE)
			g_struct.status = OUTSIDE;
		else
			g_struct.status = IN_COTE;
	}
	return (variables->start);
}

void	pipe_and_rederaction_parceen(t_var *variables)
{
	if (g_struct.fix_cmd[variables->index_i][variables->index_j] == '|'
		&& g_struct.status == OUTSIDE)
	{
		g_struct.fix_cmd[variables->index_i][variables->index_j] = 4;
		g_struct.number_of_pipes++;
	}
	if (g_struct.fix_cmd[variables->index_i][variables->index_j] == '>'
		&& g_struct.status == OUTSIDE)
	{
		g_struct.fix_cmd[variables->index_i][variables->index_j] = 2;
		g_struct.if_rediraction = 1;
	}
	if (g_struct.fix_cmd[variables->index_i][variables->index_j] == '<'
		&& g_struct.status == OUTSIDE)
	{
		g_struct.fix_cmd[variables->index_i][variables->index_j] = 5;
		g_struct.if_rediraction = 1;
	}
}

char	*_get_env(t_list *head, int j, int trim, char *expande_variable)
{
	int	i;

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

char	*my_getenv(t_list *head, char *var, int trim)
{
	int		j;
	char	*expande_variable;

	j = 0;
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
					expande_variable = _get_env(head, \
					j, trim, expande_variable);
					return (expande_variable);
				}
				j++;
			}
		}
		head = head->next;
	}
	return (expande_variable);
}

char	*split_variable_or_not(char *variable)
{
	if (g_struct.status == IN_DCOTE)
		variable = my_getenv(g_struct.list, variable, 0);
	else
		variable = my_getenv(g_struct.list, variable, 1);
	return (variable);
}

char	*is_alphabet_after_dolar(t_var *variables, \
char *whotout_expande, char *my_string, int end)
{
	char	*str;
	char	*variable;

	variable = ft_substr(whotout_expande, variables->index_j + 1, (end
				- (variables->index_j + 1)));
	variable = split_variable_or_not(variable);
	if (variable)
	{
		my_string = ft_strjoin(my_string, variable);
		if (g_struct.ambiguous == 1)
		{
			str = ft_strtrim(my_string, "\003\000");
			if (!str || (ft_strlen(str) == 0 \
			&& ((whotout_expande[variables->index_j - 1] == 3 \
			&& (whotout_expande[end] == 3 || whotout_expande[end] == 0))
						|| ft_strchr(variable, 3))))
				g_struct.error_ambiguous = 1;
			free(str);
		}
		free(variable);
	}
	variables->index_j = end - 1;
	return (my_string);
}

char	*variables_parceen(t_var *variables, \
char *whotout_expande, char *my_string)
{
	int		end;
	char	*variable;

	end = variables->index_j + 1;
	while (whotout_expande[end] && (ft_isalpha(whotout_expande[end]) \
	|| ft_isdigit(whotout_expande[end]) || whotout_expande[end] == '_'))
		end++;
	if (g_struct.status == IN_DCOTE || g_struct.status == OUTSIDE)
	{
		if (ft_isdigit(whotout_expande[variables->index_j + 1]))
			variables->index_j++;
		else if (ft_isalpha(whotout_expande[variables->index_j + 1])
			|| whotout_expande[variables->index_j + 1] == '_')
			my_string = is_alphabet_after_dolar(variables, \
			whotout_expande, my_string, end);
	}
	if (g_struct.status == IN_COTE)
	{
		variable = ft_substr(whotout_expande, variables->index_j, (end \
			- variables->index_j));
		my_string = ft_strjoin_v2(my_string, variable);
		variables->index_j = end - 1;
	}
	return (my_string);
}

char	*other_character_after_dolar(char *whotout_expande, char *my_string,
		t_var *variables)
{
	if (whotout_expande[variables->index_j + 1] == '?')
	{
		if (g_struct.status != IN_COTE)
		{
			variables->index_j++;
			my_string = \
			ft_strjoin(my_string, ft_itoa(g_struct.exit_status));
			variables->start = variables->index_j;
		}
	}
	else if ((whotout_expande[variables->index_j + 1] == 34 \
	|| whotout_expande[variables->index_j + 1] == 39) \
	&& g_struct.status == OUTSIDE)
		variables->start = variables->index_j;
	else if (!ft_isalnum(whotout_expande[variables->index_j + 1]) \
	&& whotout_expande[variables->index_j + 1] != '$')
	{
		variables->index_j++;
		variables->start = variables->index_j;
	}
	return (my_string);
}

char	*expande_all(char *whotout_expande, char *my_string,
		t_var *variables)
{
	if (ft_isalnum(whotout_expande[variables->index_j + 1]) \
	|| whotout_expande[variables->index_j + 1] == '_')
	{
		if (whotout_expande[variables->index_j + 1])
		{
			variables->start++;
			my_string = variables_parceen(variables, \
			whotout_expande, my_string);
			variables->start = variables->index_j;
		}
	}
	else
	{
		my_string = other_character_after_dolar(whotout_expande, \
		my_string, variables);
	}
	return (my_string);
}

char	*exit_status(char *my_string, t_var *variables)
{
	if (g_struct.status != IN_COTE)
	{
		variables->index_j++;
		my_string = ft_strjoin_v2(my_string, \
		ft_itoa(g_struct.exit_status));
		variables->start = variables->index_j;
	}
	else
		variables->start = variables->index_j - 1;
	return (my_string);
}

char	*_not_alphanum_after_dolar(char *whotout_expande, char *my_string,
		t_var *variables)
{
	if (whotout_expande[variables->index_j + 1] == '?')
		my_string = exit_status(my_string, variables);
	else if (g_struct.status != OUTSIDE \
		&& (whotout_expande[variables->index_j + 1] == 8 \
		|| whotout_expande[variables->index_j + 1] == 6))
		variables->start = variables->index_j - 1;
	else if (!ft_isalnum(whotout_expande[variables->index_j + 1]) \
	&& whotout_expande[variables->index_j + 1] != '$' \
	&& whotout_expande[variables->index_j + 1] != 8 \
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
	return (my_string);
}

char	*variables_parceen_utils(char *whotout_expande, char *my_string,
		t_var *variables)
{
	if (ft_isalnum(whotout_expande[variables->index_j + 1]) \
	|| whotout_expande[variables->index_j + 1] == '_')
	{
		if (whotout_expande[variables->index_j + 1])
		{
			variables->start++;
			my_string = variables_parceen(variables, whotout_expande,
					my_string);
			variables->start = variables->index_j;
		}
	}
	else
		my_string = _not_alphanum_after_dolar(whotout_expande, \
		my_string, variables);
	return (my_string);
}

int	change_quotes_and_pipe_and_rederaction(t_var *variables)
{
	while (g_struct.fix_cmd[variables->index_i][variables->index_j])
	{
		quote_and_dquote(variables);
		pipe_and_rederaction_parceen(variables);
		if (g_struct.fix_cmd[variables->index_i][variables->index_j] == 4 &&
			((variables->index_j == 0 && variables->index_i == 0) \
			|| (variables->index_j - 1 >= 0 && g_struct.fix_cmd \
			[variables->index_i][variables->index_j - 1] == 4)
			|| (g_struct.fix_cmd[variables->index_i][variables->index_j
			+ 1] == 0 && g_struct.fix_cmd[variables->index_i + 1] == 0)))
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			while (g_struct.fix_cmd[variables->index_i])
			{
				free(g_struct.fix_cmd[variables->index_i]);
				variables->index_i++;
			}
			free(g_struct.fix_cmd);
			if (g_struct.the_commande)
				free(g_struct.the_commande);
			return (258);
		}
		variables->index_j++;
	}
	return (0);
}

int	parccen_part(t_var *variables)
{
	while (g_struct.fix_cmd[variables->index_i])
	{
		variables->index_j = 0;
		g_struct.status = OUTSIDE;
		if (change_quotes_and_pipe_and_rederaction(variables) == 258)
			return (258);
		if (g_struct.status != OUTSIDE)
		{
			ft_putstr_fd
				("minishell: unexpected EOF while looking for matching\n", 2);
			return (2);
		}
		g_struct.the_commande = ft_strjoin_v2(g_struct.the_commande, \
			g_struct.fix_cmd[variables->index_i]);
		if (g_struct.fix_cmd[variables->index_i + 1])
			g_struct.the_commande = ft_strjoin(g_struct.the_commande, \
			"\003\000");
		g_struct.fix_cmd[variables->index_i] = 0;
		variables->index_i++;
	}
	return (1);
}

void	initialisaion(t_var *variables, int c_of_s)
{
	g_struct.each_cmd[variables->index_i].files[c_of_s].OUTPUT = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].APPEND = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_O = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_I = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].INPUT = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].HERDOC = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].ERROR_SYNTACSO = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].ERROR_SYNTACSI = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].HERDOC_OPTION = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].ambiguous = 0;
}

char	*expande_variables_insied_herdoc(t_var *indes, char *buffer,
		char *herdoc)
{
	char	*buffer_tmp;

	indes->start = indes->index_i;
	while (ft_isalnum(buffer[indes->index_i]) \
	|| buffer[indes->index_i] == '_')
		indes->index_i++;
	buffer_tmp = ft_substr(buffer, indes->start, indes->index_i - indes->start);
	herdoc = ft_strjoin_v2(herdoc, my_getenv(g_struct.list, buffer_tmp, 0));
	free(buffer_tmp);
	indes->start = indes->index_i;
	return (herdoc);
}

char	*what_insied_herdoc(t_var *indes, char *buffer,
		char *herdoc)
{
	if ((buffer[indes->index_i] == '$' && buffer[indes->index_i + 1]
			&& buffer[indes->index_i + 1] != ' '))
	{
		herdoc = ft_strjoin_v2(herdoc, ft_substr(buffer, indes->start,
					indes->index_i - indes->start));
		indes->index_i++;
		if (buffer[indes->index_i] == '?')
		{
			herdoc = ft_strjoin_v2(herdoc, ft_itoa(g_struct.exit_status));
			indes->index_i++;
			indes->start = indes->index_i;
		}
		else
			herdoc = expande_variables_insied_herdoc(indes, buffer, herdoc);
		indes->index_i--;
	}
	return (herdoc);
}

char	*fill_herdoc(char *buffer, t_var *indes, char *herdoc)
{
	indes->index_i = -1;
	indes->start = 0;
	while (buffer[++indes->index_i])
	{
		herdoc = what_insied_herdoc(indes, buffer, herdoc);
		if (!buffer[indes->index_i])
			break ;
	}
	herdoc = ft_strjoin_v2(herdoc, ft_substr(buffer, indes->start, \
	indes->index_i - indes->start));
	return (herdoc);
}

char	*read_line_herdoc(int c_of_s, t_var *variables,
		char *herdoc)
{
	char	*buffer;
	t_var	indes;

	buffer = 0;
	indes.index_i = 0;
	indes.start = 0;
	while (1)
	{
		buffer = readline("> ");
		if (!buffer || !ft_strncmp(buffer,
				g_struct.each_cmd[variables->index_i].files[c_of_s].files,
				ft_strlen(buffer) + 1))
			break ;
		if (ft_strchr(buffer, '$')
			&& g_struct.each_cmd[c_of_s].files[c_of_s].HERDOC_OPTION == 0)
			herdoc = fill_herdoc(buffer, &indes, herdoc);
		else
			herdoc = ft_strjoin(herdoc, buffer);
		herdoc = ft_strjoin(herdoc, "\n");
	}
	return (herdoc);
}

void	parrcing_of_insied_herdoc(t_var *variables, int c_of_s)
{
	int		fd_by_pipe[2];
	char	*herdoc;

	herdoc = ft_strdup("");
	pipe(fd_by_pipe);
	herdoc = read_line_herdoc(c_of_s, variables, herdoc);
	ft_putstr_fd(herdoc, fd_by_pipe[1]);
	close(fd_by_pipe[1]);
	free(herdoc);
	g_struct.fils_descreprot = fd_by_pipe[0];
}

int	remove_quotes_and_expande_variables_in_input(t_var \
*variables, int cas, int if_error)
{
	char	**str;

	variables->start = variables->index_j - 1;
	g_struct.each_cmd[variables->index_i].files[cas].files = ft_calloc(1, 1);
	if (g_struct.each_cmd[variables->index_i].files[cas].number_of_I == 2)
		g_struct.each_cmd[variables->index_i].files[cas].HERDOC = 1;
	g_struct.ambiguous = 1;
	g_struct.error_ambiguous = 0;
	quotes(variables, cas);
	str = ft_split(g_struct.each_cmd[variables->index_i].files[cas].files, 3);
	if_error = 0;
	if (str[if_error])
	{
		free(g_struct.each_cmd[variables->index_i].files[cas].files);
		g_struct.each_cmd[variables->index_i].files[cas].files = 0;
	}
	while (str[if_error])
	{
		g_struct.each_cmd[variables->index_i].files[cas].files \
		= ft_strdup(str[if_error]);
		free(str[if_error]);
		if_error++;
	}
	free(str);
	return (if_error);
}

void	syntax_error(t_var *variables)
{
	int	i;

	i = fork();
	if (i == 0)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		exit(1);
	}
	wait(&i);
	i = 0;
	while (g_struct.each_cmd[i].files)
	{
		free(g_struct.each_cmd[i].files);
		i++;
	}
	free(g_struct.each_cmd);
	free(g_struct.tmp_cmd);
	free(g_struct.the_commande);
	while (g_struct.splite_pipe[variables->index_i])
	{
		free(g_struct.splite_pipe[variables->index_i]);
		variables->index_i++;
	}
	free(g_struct.splite_pipe);
}

int	inistialisation_input(t_var *variables, int c_of_s)
{
	int	if_error;

	if_error = 0;
	if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_I > 2)
		if_error = 1;
	if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_O
		&& g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_I)
		if_error = 1;
	if (!g_struct.tmp_cmd[variables->index_j])
		if_error = 1;
	if (if_error == 1)
		return (syntax_error(variables), -1);
	if_error = remove_quotes_and_expande_variables_in_input(variables, \
		c_of_s, if_error);
	if ((g_struct.error_ambiguous == 1 && if_error == 0) || if_error > 1)
		g_struct.each_cmd[variables->index_i].files[c_of_s].ambiguous = 1;
	if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_I == 1)
		g_struct.each_cmd[variables->index_i].files[c_of_s].INPUT = 1;
	else if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_I \
		== 2)
		parrcing_of_insied_herdoc(variables, c_of_s);
	variables->index_j = variables->end - 1;
	return (0);
}

void	remove_quotes_and_expande_in_rederaction(t_var *variables, int c_of_s)
{
	if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_O == 2)
	g_struct.each_cmd[variables->index_i].files[c_of_s].APPEND = 1;
	else if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_O \
		== 1)
		g_struct.each_cmd[variables->index_i].files[c_of_s].OUTPUT = 1;
	variables->start = variables->index_j - 1;
	g_struct.each_cmd[variables->index_i].files[c_of_s].files = ft_calloc(1, 1);
	g_struct.ambiguous = 1;
	g_struct.error_ambiguous = 0;
	quotes(variables, c_of_s);
}

int	if_multiple_argemnt_in_rederaction_files(t_var \
*variables, int c_of_s, int if_error)
{
	char	**str;

	remove_quotes_and_expande_in_rederaction(variables, c_of_s);
	str = ft_split(g_struct.each_cmd[variables->index_i].files[c_of_s].files,
			3);
	if (str[if_error])
	{
		free(g_struct.each_cmd[variables->index_i].files[c_of_s].files);
		g_struct.each_cmd[variables->index_i].files[c_of_s].files = 0;
	}
	while (str[if_error])
	{
		g_struct.each_cmd[variables->index_i].files[c_of_s].\
		files = ft_strdup(str[if_error]);
		free(str[if_error]);
		if_error++;
	}
	free(str);
	return (if_error);
}

int	inistialisation_output(t_var *variables, int c_of_s)
{
	int	if_error;

	if_error = 0;
	if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_O > 2)
		if_error = 1;
	if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_O
		&& g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_I)
		if_error = 1;
	if (!g_struct.tmp_cmd[variables->index_j])
		if_error = 1;
	if (if_error == 1)
	{
		syntax_error(variables);
		return (-1);
	}
	if_error = if_multiple_argemnt_in_rederaction_files(variables, \
	c_of_s, 0);
	if ((g_struct.error_ambiguous == 1 && if_error == 0) || if_error > 1)
		g_struct.each_cmd[variables->index_i].files[c_of_s].ambiguous = 1;
	variables->index_j = variables->end - 1;
	return (0);
}

int	how_many_rederaction_output(t_var *variables, int c_of_s)
{
	if (g_struct.tmp_cmd[variables->index_j] == 2)
	{
		while (g_struct.tmp_cmd[variables->index_j] == 2)
		{
			g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_O++;
			variables->index_j++;
		}
	}
	if (g_struct.tmp_cmd[variables->index_j] == 5)
	{
		while (g_struct.tmp_cmd[variables->index_j] == 5)
		{
			g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_I++;
			variables->index_j++;
		}
	}
	if (g_struct.tmp_cmd[variables->index_j] == 0
		|| (g_struct.tmp_cmd[variables->index_j] != 5
			&& g_struct.tmp_cmd[variables->index_j] != 2)
		|| (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_O
			&& g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_I))
		return (1);
	return (0);
}

void	rediraction_calculate_output(t_var *variables,
		int c_of_s)
{
	while (g_struct.tmp_cmd[variables->index_j]
		&& (g_struct.tmp_cmd[variables->index_j] == 2
			|| g_struct.tmp_cmd[variables->index_j] == 5))
	{
		if (how_many_rederaction_output(variables, c_of_s))
			break ;
		variables->index_j++;
	}
	while (g_struct.tmp_cmd[variables->index_j]
		&& g_struct.tmp_cmd[variables->index_j] == 3)
		variables->index_j++;
	variables->end = variables->index_j;
	while (g_struct.tmp_cmd[variables->end]
		&& g_struct.tmp_cmd[variables->end] != 2
		&& g_struct.tmp_cmd[variables->end] != 5
		&& g_struct.tmp_cmd[variables->end] != 3)
	{
		if (g_struct.tmp_cmd[variables->end] == 8
			|| g_struct.tmp_cmd[variables->end] == 6)
			g_struct.each_cmd[variables->index_i].files[c_of_s].HERDOC_OPTION \
			= 1;
		variables->end++;
	}
}

int	how_many_rederaction_input(t_var *variables, int c_of_s)
{
	if (g_struct.tmp_cmd[variables->index_j] == 5)
	{
		while (g_struct.tmp_cmd[variables->index_j] == 5)
		{
			g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_I++;
			variables->index_j++;
		}
	}
	if (g_struct.tmp_cmd[variables->index_j] == 2)
	{
		while (g_struct.tmp_cmd[variables->index_j] == 2)
		{
			g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_O++;
			variables->index_j++;
		}
	}
	if (g_struct.tmp_cmd[variables->index_j] == 0
		|| (g_struct.tmp_cmd[variables->index_j] != 5
			&& g_struct.tmp_cmd[variables->index_j] != 2)
		|| (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_O
			&& g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_I))
		return (1);
	return (0);
}

void	rediraction_calculate_input(t_var *variables,
		int c_of_s)
{
	while (g_struct.tmp_cmd[variables->index_j]
		&& (g_struct.tmp_cmd[variables->index_j] == 2
			|| g_struct.tmp_cmd[variables->index_j] == 5))
	{
		if (how_many_rederaction_input(variables, c_of_s))
			break ;
		variables->index_j++;
	}
	while (g_struct.tmp_cmd[variables->index_j]
		&& g_struct.tmp_cmd[variables->index_j] == 3)
		variables->index_j++;
	variables->end = variables->index_j;
	while (g_struct.tmp_cmd[variables->end]
		&& g_struct.tmp_cmd[variables->end] != 2
		&& g_struct.tmp_cmd[variables->end] != 5
		&& g_struct.tmp_cmd[variables->end] != 3)
	{
		if (g_struct.tmp_cmd[variables->end] == 8
			|| g_struct.tmp_cmd[variables->end] == 6)
			g_struct.each_cmd[variables->index_i].files[c_of_s].HERDOC_OPTION \
			= 1;
		variables->end++;
	}
}

void	expande_variables_in_comande_parcen_part(t_var *variables)
{
	variables->start++;
	g_struct.the_commande = ft_strjoin_v2(g_struct.the_commande, \
	ft_substr(g_struct.tmp_cmd, variables->start, variables->index_j \
	- variables->start));
	variables->start = variables->index_j;
	if (g_struct.tmp_cmd[variables->index_j + 1])
	{
		g_struct.parccer = 1;
		g_struct.the_commande = variables_parceen_utils(g_struct.tmp_cmd, \
		g_struct.the_commande, variables);
	}
}

void	comande_parcen_part(t_var *variables)
{
	if (g_struct.tmp_cmd[variables->index_j] == 8 \
			&& g_struct.status != IN_COTE)
	{
		if (g_struct.status == IN_DCOTE)
			g_struct.status = OUTSIDE;
		else
			g_struct.status = IN_DCOTE;
	}
	else if (g_struct.tmp_cmd[variables->index_j] == 6 \
			&& g_struct.status != IN_DCOTE)
	{
		if (g_struct.status == IN_COTE)
			g_struct.status = OUTSIDE;
		else
			g_struct.status = IN_COTE;
	}
	else if (g_struct.tmp_cmd[variables->index_j] == '$' \
	&& g_struct.tmp_cmd[variables->index_j + 1] \
	&& g_struct.tmp_cmd[variables->index_j + 1] != ' ' \
	&& g_struct.tmp_cmd[variables->index_j + 1] != 3)
		expande_variables_in_comande_parcen_part(variables);
}

void	commande_and_args(t_var *variables)
{
	variables->end = variables->index_j;
	variables->start = variables->index_j - 1;
	g_struct.ambiguous = 2;
	while (g_struct.tmp_cmd[variables->end]
		&& (g_struct.tmp_cmd[variables->end] != 2
			&& g_struct.tmp_cmd[variables->end] != 5))
		variables->end++;
	while (variables->index_j < variables->end)
	{
		comande_parcen_part(variables);
		variables->index_j++;
	}
	variables->start++;
	g_struct.the_commande = ft_strjoin_v2(g_struct.the_commande, \
	ft_substr(g_struct.tmp_cmd, variables->start, \
	variables->index_j - variables->start));
	variables->index_j = variables->end - 1;
}

void	if_rediraction_is_existe(t_var *variables)
{
	if (ft_strchr(g_struct.tmp_cmd, 2)
		|| ft_strchr(g_struct.splite_pipe[variables->index_i], 5))
	{
		variables->end = 0;
		while (g_struct.tmp_cmd[variables->index_j])
		{
			if (g_struct.tmp_cmd[variables->index_j] == 2
				|| g_struct.tmp_cmd[variables->index_j] == 5)
			{
				while (g_struct.tmp_cmd[variables->index_j] == 2)
					variables->index_j++;
				variables->end++;
			}
			if (!g_struct.tmp_cmd[variables->index_j])
				break ;
			variables->index_j++;
		}
		g_struct.each_cmd[variables->index_i].files = \
		ft_calloc(sizeof(t_files), (variables->end + 1));
	}
}

int	commande_and_rederaction_parceen(t_var *variables,
		int c_of_s)
{
	int	i;

	if (g_struct.tmp_cmd[variables->index_j] && \
		g_struct.tmp_cmd[variables->index_j] == 2)
	{
		initialisaion(variables, c_of_s);
		rediraction_calculate_output(variables, c_of_s);
		i = inistialisation_output(variables, c_of_s);
		if (i != 0)
			return (i);
		c_of_s++;
	}
	else if (g_struct.tmp_cmd[variables->index_j] \
		&& g_struct.tmp_cmd[variables->index_j] == 5)
	{
		initialisaion(variables, c_of_s);
		rediraction_calculate_input(variables, c_of_s);
		i = inistialisation_input(variables, c_of_s);
		if (i != 0)
			return (i);
		c_of_s++;
	}
	else
		commande_and_args(variables);
	return (c_of_s);
}

void	remove_double_quotes(t_var *variables, int c_of_s)
{
	if (g_struct.status == IN_DCOTE)
	{
		g_struct.each_cmd[variables->index_i].files[c_of_s].files \
		= ft_strjoin(g_struct.each_cmd[variables->index_i].files[c_of_s].files, \
		"");
		g_struct.status = OUTSIDE;
	}
	else
		g_struct.status = IN_DCOTE;
	variables->start++;
	g_struct.each_cmd[variables->index_i].files[c_of_s].files = \
	ft_strjoin_v2(g_struct.each_cmd[variables->index_i].\
	files[c_of_s].files, ft_substr(g_struct.tmp_cmd, \
	variables->start, variables->index_j - variables->start));
	variables->start = variables->index_j;
}

void	remove_single_quotes(t_var *variables, int c_of_s)
{
	if (g_struct.status == IN_COTE)
	{
		g_struct.status = OUTSIDE;
		g_struct.each_cmd[variables->index_i].files[c_of_s].files = \
		ft_strjoin(g_struct.each_cmd[variables->index_i].\
		files[c_of_s].files, "");
	}
	else
		g_struct.status = IN_COTE;
	variables->start++;
	g_struct.each_cmd[variables->index_i].files[c_of_s].files \
	= ft_strjoin_v2(g_struct.each_cmd[variables->index_i] \
	.files[c_of_s].files, ft_substr(g_struct.tmp_cmd, \
	variables->start, variables->index_j - variables->start));
	variables->start = variables->index_j;
}

void	expande_variables(t_var *var, int cas)
{
	var->start++;
	g_struct.each_cmd[var->index_i].files[cas].files = \
	ft_strjoin_v2(g_struct.each_cmd[var->index_i].files[cas].files, \
	ft_substr(g_struct.tmp_cmd, var->start \
	, var->index_j - var->start));
	var->start = var->index_j;
	if (g_struct.tmp_cmd[var->index_j + 1])
		g_struct.each_cmd[var->index_i].files[cas].files = \
		expande_all(g_struct.tmp_cmd, \
		g_struct.each_cmd[var->index_i].files[cas].files, var);
}

void	quotes(t_var *variables, int c_of_s)
{
	while (variables->index_j < variables->end)
	{
		if (g_struct.tmp_cmd[variables->index_j] == 8
			&& g_struct.status != IN_COTE)
			remove_double_quotes(variables, c_of_s);
		else if (g_struct.tmp_cmd[variables->index_j] == 6 \
				&& g_struct.status != IN_DCOTE)
			remove_single_quotes(variables, c_of_s);
		else if (g_struct.tmp_cmd[variables->index_j] == '$' \
		&& g_struct.tmp_cmd[variables->index_j + 1] \
		&& g_struct.tmp_cmd[variables->index_j + 1] != ' ' \
		&& g_struct.tmp_cmd[variables->index_j + 1] != 3 \
		&& g_struct.each_cmd[variables->index_i].files[c_of_s].HERDOC == 0)
			expande_variables(variables, c_of_s);
		variables->index_j++;
	}
	variables->start++;
	g_struct.each_cmd[variables->index_i].files[c_of_s].files = \
	ft_strjoin_v2(g_struct.each_cmd[variables->index_i].files[c_of_s].files, \
	ft_substr(g_struct.tmp_cmd, variables->start, \
	variables->index_j - variables->start));
}

void	remove_double_quotes_in_commande_parccing_part(t_var *variables)
{
	if (g_struct.status == IN_DCOTE)
	{
		g_struct.tmp_cmd = ft_strjoin(g_struct.tmp_cmd, "");
		g_struct.status = OUTSIDE;
	}
	else
		g_struct.status = IN_DCOTE;
	variables->start++;
	g_struct.tmp_cmd = ft_strjoin_v2(g_struct.tmp_cmd, \
	ft_substr(g_struct.each_cmd[variables->index_i].cmd[variables->end], \
	variables->start, variables->index_j - variables->start));
	variables->start = variables->index_j;
}

void	remove_single_quotes_in_commande_parccing_part(t_var *variables)
{
	if (g_struct.status == IN_COTE)
	{
		g_struct.status = OUTSIDE;
		g_struct.tmp_cmd = ft_strjoin(g_struct.tmp_cmd, "");
	}
	else
		g_struct.status = IN_COTE;
	variables->start++;
	g_struct.tmp_cmd = ft_strjoin_v2(g_struct.tmp_cmd, \
	ft_substr(g_struct.each_cmd[variables->index_i].cmd[variables->end], \
	variables->start, variables->index_j - variables->start));
	variables->start = variables->index_j;
}

int	other_string_beffor_end_of_line(t_var *variables, int cas)
{
	variables->start++;
	g_struct.tmp_cmd = ft_strjoin_v2(g_struct.tmp_cmd, \
	ft_substr(g_struct.each_cmd[variables->index_i].cmd \
	[variables->end], variables->start, variables->index_j \
	- variables->start));
	free(g_struct.each_cmd[variables->index_i].cmd[variables->end]);
	g_struct.each_cmd[variables->index_i].cmd[variables->end] = 0;
	if (!(ft_strchr(g_struct.tmp_cmd, 7) && \
		ft_strlen(g_struct.tmp_cmd) == 1))
	{
		g_struct.each_cmd[variables->index_i].cmd[cas] \
		= ft_strdup(g_struct.tmp_cmd);
		cas++;
	}
	free(g_struct.tmp_cmd);
	g_struct.tmp_cmd = 0;
	variables->end++;
	return (cas);
}

void	splite_commande(t_var *variables)
{
	g_struct.each_cmd[variables->index_i].cmd \
	= ft_split(g_struct.the_commande, 3);
	free(g_struct.tmp_cmd);
	g_struct.tmp_cmd = 0;
	variables->end = 0;
}

void	quotes_comnde(t_var *variables)
{
	int	cas;

	splite_commande(variables);
	cas = 0;
	while (g_struct.each_cmd[variables->index_i].cmd[variables->end])
	{
		variables->index_j = 0;
		variables->start = -1;
		g_struct.tmp_cmd = ft_calloc(1, 1);
		while (g_struct.each_cmd[variables->index_i] \
		.cmd[variables->end][variables->index_j])
		{
			if (g_struct.each_cmd[variables->index_i] \
			.cmd[variables->end][variables->index_j] == 8
				&& g_struct.status != IN_COTE)
				remove_double_quotes_in_commande_parccing_part(variables);
			else if (g_struct.each_cmd[variables->index_i] \
			.cmd[variables->end][variables->index_j] == 6
					&& g_struct.status != IN_DCOTE)
				remove_single_quotes_in_commande_parccing_part(variables);
			variables->index_j++;
		}
		cas = other_string_beffor_end_of_line(variables, cas);
	}
}

int	partition_of_comande_and_rederaction(t_var *variables, int c_of_s)
{
	g_struct.status = OUTSIDE;
	g_struct.tmp_cmd = ft_strdup(g_struct.splite_pipe[variables->index_i]);
	variables->index_j = 0;
	g_struct.the_commande = ft_calloc(1, 1);
	if_rediraction_is_existe(variables);
	c_of_s = 0;
	variables->index_j = 0;
	while (g_struct.tmp_cmd[variables->index_j])
	{
		g_struct.parccer = 0;
		c_of_s = commande_and_rederaction_parceen(variables,
				c_of_s);
		if (c_of_s < 0)
			return (c_of_s);
		variables->index_j++;
	}
	quotes_comnde(variables);
	free(g_struct.splite_pipe[variables->index_i]);
	g_struct.splite_pipe[variables->index_i] = 0;
	free(g_struct.the_commande);
	g_struct.the_commande = 0;
	return (0);
}

int	partition_part(t_var *variables)
{
	int	c_of_s;

	c_of_s = 0;
	variables->end = 0;
	variables->index_i = 0;
	g_struct.fils_descreprot = 0;
	while (g_struct.splite_pipe[variables->index_i])
	{
		c_of_s = partition_of_comande_and_rederaction(variables, c_of_s);
		if (c_of_s != 0)
			return (c_of_s);
		variables->index_i++;
	}
	free(g_struct.splite_pipe);
	return (0);
}

int	fix_arg(void)
{
	t_var	variables;

	variables.index_i = 0;
	variables.index_j = 0;
	variables.start = -1;
	g_struct.number_of_pipes = 1;
	g_struct.the_commande = 0;
	g_struct.the_commande = ft_calloc(1, 1);
	variables.index_i = parccen_part(&variables);
	if (variables.index_i != 1)
		return (variables.index_i);
	free(g_struct.fix_cmd);
	g_struct.splite_pipe = ft_split(g_struct.the_commande, 4);
	free(g_struct.the_commande);
	g_struct.the_commande = 0;
	variables.index_i = 0;
	g_struct.each_cmd = ft_calloc(sizeof(t_each_command), \
	g_struct.number_of_pipes + 1);
	variables.index_i = partition_part(&variables);
	if (variables.index_i == -1)
		return (258);
	if (variables.index_i == -2)
		return (1);
	return (0);
}
