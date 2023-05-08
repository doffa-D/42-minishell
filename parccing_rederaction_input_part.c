/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccing_rederaction_input_part.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:11:31 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 15:29:13 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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