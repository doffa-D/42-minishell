/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccing_represent_pipe_and_rediraction.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:46:18 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 15:23:04 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"

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
