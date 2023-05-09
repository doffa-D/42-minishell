/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccing_rederaction_input_part.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:11:31 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 15:51:39 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	calculat_how_many_argemnt_in_vaiable(t_var \
*variables, int cas, int if_error, char **str)
{
	if (str[if_error])
	{
		free(g_struct.each_cmd[variables->index_i].files[cas].files);
		g_struct.each_cmd[variables->index_i].files[cas].files = 0;
	}
	while (str[if_error])
	{
		g_struct.each_cmd[variables->index_i].files[cas].files \
		= ft_strdup(str[if_error]);
		free_parccing_part_after_error \
		(g_struct.each_cmd[variables->index_i].files[cas].files);
		free(str[if_error]);
		if_error++;
	}
	return (if_error);
}

int	remove_quotes_and_expande_variables_in_input(t_var \
*variables, int cas, int if_error)
{
	char	**str;

	variables->start = variables->index_j - 1;
	g_struct.each_cmd[variables->index_i].files[cas].files = ft_calloc(1, 1);
	free_parccing_part_after_error \
	(g_struct.each_cmd[variables->index_i].files[cas].files);
	if (g_struct.each_cmd[variables->index_i].files[cas].number_of_i == 2)
		g_struct.each_cmd[variables->index_i].files[cas].herdoc = 1;
	g_struct.ambiguous = 1;
	g_struct.error_ambiguous = 0;
	quotes(variables, cas);
	str = ft_split(g_struct.each_cmd[variables->index_i].files[cas].files, 3);
	free_parccing_part_after_error(str);
	if_error = 0;
	if_error = calculat_how_many_argemnt_in_vaiable \
	(variables, cas, if_error, str);
	free(str);
	return (if_error);
}

int	inistialisation_input(t_var *variables, int c_of_s)
{
	int	if_error;

	if_error = 0;
	if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_i > 2)
		if_error = 1;
	if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_o
		&& g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_i)
		if_error = 1;
	if (!g_struct.tmp_cmd[variables->index_j])
		if_error = 1;
	if (if_error == 1)
		return (syntax_error(variables), -1);
	if_error = remove_quotes_and_expande_variables_in_input(variables, \
		c_of_s, if_error);
	if ((g_struct.error_ambiguous == 1 && if_error == 0) || if_error > 1)
		g_struct.each_cmd[variables->index_i].files[c_of_s].ambiguous = 1;
	if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_i == 1)
		g_struct.each_cmd[variables->index_i].files[c_of_s].input = 1;
	else if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_i \
		== 2)
		parrcing_of_insied_herdoc(variables, c_of_s);
	variables->index_j = variables->end - 1;
	return (0);
}
