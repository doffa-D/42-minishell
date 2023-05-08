/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccing_expande_variabls_in_commande.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:14:59 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 15:15:08 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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