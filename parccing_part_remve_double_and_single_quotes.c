/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccing_part_remve_double_and_single_quote        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:17:39 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 14:20:01 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	splite_commande(t_var *variables)
{
	g_struct.each_cmd[variables->index_i].cmd \
	= ft_split(g_struct.the_commande, 3);
	free(g_struct.tmp_cmd);
	g_struct.tmp_cmd = 0;
	variables->end = 0;
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