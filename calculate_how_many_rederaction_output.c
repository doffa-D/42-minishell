/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_how_many_rederaction_output.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:03:50 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 01:29:09 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	how_many_rederaction_output(t_var *variables, int c_of_s)
{
	if (g_struct.tmp_cmd[variables->index_j] == 2)
	{
		while (g_struct.tmp_cmd[variables->index_j] == 2)
		{
			g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_o++;
			variables->index_j++;
		}
	}
	if (g_struct.tmp_cmd[variables->index_j] == 5)
	{
		while (g_struct.tmp_cmd[variables->index_j] == 5)
		{
			g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_i++;
			variables->index_j++;
		}
	}
	if (g_struct.tmp_cmd[variables->index_j] == 0
		|| (g_struct.tmp_cmd[variables->index_j] != 5
			&& g_struct.tmp_cmd[variables->index_j] != 2)
		|| (g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_o
			&& g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_i))
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
			g_struct.each_cmd[variables->index_i].files[c_of_s].herdoc_option \
			= 1;
		variables->end++;
	}
}
