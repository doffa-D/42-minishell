/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_in_rederaction_parccing_part.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:21:05 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/13 00:30:43 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_double_quotes(t_var *variables, int c_of_s)
{
	if (g_struct.status == IN_DCOTE)
	{
		g_struct.each_cmd[variables->index_i].files[c_of_s].files = ft_strjoin \
		(g_struct.each_cmd[variables->index_i].files[c_of_s].files, "");
		free_parccing_part_after_error(g_struct.each_cmd \
		[variables->index_i].files[c_of_s].files);
		g_struct.status = OUTSIDE;
	}
	else
		g_struct.status = IN_DCOTE;
	variables->start++;
	g_struct.each_cmd[variables->index_i].files[c_of_s].files = \
	ft_strjoin_v2(g_struct.each_cmd[variables->index_i].\
	files[c_of_s].files, ft_substr(g_struct.tmp_cmd, \
	variables->start, variables->index_j - variables->start));
	free_parccing_part_after_error(g_struct.each_cmd \
	[variables->index_i].files[c_of_s].files);
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
		free_parccing_part_after_error \
		(g_struct.each_cmd[variables->index_i].files[c_of_s].files);
	}
	else
		g_struct.status = IN_COTE;
	variables->start++;
	g_struct.each_cmd[variables->index_i].files[c_of_s].files \
	= ft_strjoin_v2(g_struct.each_cmd[variables->index_i] \
	.files[c_of_s].files, ft_substr(g_struct.tmp_cmd, \
	variables->start, variables->index_j - variables->start));
	free_parccing_part_after_error \
	(g_struct.each_cmd[variables->index_i].files[c_of_s].files);
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
	free_parccing_part_after_error \
	(g_struct.each_cmd[var->index_i].files[cas].files);
	if (g_struct.tmp_cmd[var->index_j + 1])
		g_struct.each_cmd[var->index_i].files[cas].files = \
		expande_all(g_struct.tmp_cmd, g_struct.each_cmd \
		[var->index_i].files[cas].files, var);
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
		&& g_struct.each_cmd[variables->index_i].files[c_of_s].herdoc == 0)
			expande_variables(variables, c_of_s);
		variables->index_j++;
	}
	variables->start++;
	g_struct.each_cmd[variables->index_i].files[c_of_s].files = \
	ft_strjoin_v2(g_struct.each_cmd[variables->index_i].files[c_of_s].files, \
	ft_substr(g_struct.tmp_cmd, variables->start, \
	variables->index_j - variables->start));
	free_parccing_part_after_error \
	(g_struct.each_cmd[variables->index_i].files[c_of_s].files);
}
