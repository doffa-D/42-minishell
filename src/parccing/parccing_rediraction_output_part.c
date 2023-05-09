/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccing_rediraction_output_part.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:13:01 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 15:51:42 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_quotes_and_expande_in_rederaction(t_var *variables, int c_of_s)
{
	if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_o == 2)
		g_struct.each_cmd[variables->index_i].files[c_of_s].append = 1;
	else if (g_struct.each_cmd[variables->index_i].files[c_of_s]. \
	number_of_o == 1)
		g_struct.each_cmd[variables->index_i].files[c_of_s].output = 1;
	variables->start = variables->index_j - 1;
	g_struct.each_cmd[variables->index_i].files[c_of_s].files = ft_calloc(1, 1);
	free_parccing_part_after_error(g_struct.each_cmd[variables->index_i]. \
	files[c_of_s].files);
	g_struct.ambiguous = 1;
	g_struct.error_ambiguous = 0;
	quotes(variables, c_of_s);
}

int	if_multiple_argemnt_in_rederaction_files(t_var *variables,
	int c_of_s, int if_error)
{
	char	**str;

	remove_quotes_and_expande_in_rederaction(variables, c_of_s);
	str = ft_split(g_struct.each_cmd[variables->index_i]. \
	files[c_of_s].files, 3);
	free_parccing_part_after_error(str);
	if (str[if_error])
	{
		free(g_struct.each_cmd[variables->index_i].files[c_of_s].files);
		g_struct.each_cmd[variables->index_i].files[c_of_s].files = 0;
	}
	while (str[if_error])
	{
		g_struct.each_cmd[variables->index_i].files[c_of_s].files = \
		ft_strdup(str[if_error]);
		free_parccing_part_after_error(g_struct.each_cmd \
		[variables->index_i].files[c_of_s].files);
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
	if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_o > 2)
		if_error = 1;
	if (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_o
		&& g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_i)
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
