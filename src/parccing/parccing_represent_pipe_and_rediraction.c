/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccing_represent_pipe_and_rediraction.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:46:18 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/14 15:04:45 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	utils_pipe(void)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (g_struct.the_commande[i])
	{
		if (i == 0 && g_struct.the_commande[i] == 4)
			return (1);
		if (x == 1 && g_struct.the_commande[i] == 4)
			return (1);
		if (g_struct.the_commande[i] != 3)
			x = 0;
		if (g_struct.the_commande[i] == 4)
			x = 1;
		i++;
	}
	return (x);
}

int	change_quotes_and_pipe_and_rederaction(t_var *variables)
{
	while (g_struct.fix_cmd[variables->index_i][variables->index_j])
	{
		quote_and_dquote(variables);
		pipe_and_rederaction_parcing(variables);
		variables->index_j++;
	}
	return (0);
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

void	pipe_and_rederaction_parcing(t_var *variables)
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
