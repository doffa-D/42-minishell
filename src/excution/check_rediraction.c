/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rediraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:18:08 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 15:42:28 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_rediractions(int c_of_s)
{
	int	j;

	j = 0;
	while (g_struct.each_cmd[c_of_s].files[j].files)
	{
		_error_rediraction_in_chiled(c_of_s, j);
		if (g_struct.each_cmd[c_of_s].files[j].output == 1)
			_rediraction_output_in_chiled(c_of_s, j);
		else if (g_struct.each_cmd[c_of_s].files[j].input == 1)
			_rediraction_input_in_chiled(c_of_s, j);
		if (g_struct.each_cmd[c_of_s].files[j].append == 1)
			_rediraction_append_in_chiled(c_of_s, j);
		else if (g_struct.each_cmd[c_of_s].files[j].herdoc == 1)
		{
			dup2(g_struct.fils_descreprot, STDIN_FILENO);
			close(g_struct.fils_descreprot);
		}
		j++;
	}
	if (!g_struct.each_cmd[c_of_s].cmd[0])
		exit(0);
}
