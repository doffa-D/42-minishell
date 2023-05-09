/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_rediraction_is_exist.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:17:42 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 13:27:00 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"

void	initialisaion(t_var *variables, int c_of_s)
{
	g_struct.each_cmd[variables->index_i].files[c_of_s].output = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].append = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_o = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_i = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].input = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].herdoc = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].error_syntax_o = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].error_syntax_i = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].herdoc_option = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].ambiguous = 0;
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
		free_parccing_part_after_error \
		(g_struct.each_cmd[variables->index_i].files);
	}
}
