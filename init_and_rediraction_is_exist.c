/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_rediraction_is_exist.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:17:42 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 15:17:50 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	initialisaion(t_var *variables, int c_of_s)
{
	g_struct.each_cmd[variables->index_i].files[c_of_s].OUTPUT = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].APPEND = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_O = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].number_of_I = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].INPUT = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].HERDOC = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].ERROR_SYNTACSO = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].ERROR_SYNTACSI = 0;
	g_struct.each_cmd[variables->index_i].files[c_of_s].HERDOC_OPTION = 0;
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
	}
}
