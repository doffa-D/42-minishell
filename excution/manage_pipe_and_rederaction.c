/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe_and_rederaction.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:25:43 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 13:27:28 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"

void	handel_pipe_and_rederaction(int c_of_s)
{
	if (c_of_s > 0)
	{
		close(g_struct.each_cmd[c_of_s - 1].fd[1]);
		dup2(g_struct.each_cmd[c_of_s - 1].fd[0], STDIN_FILENO);
		close(g_struct.each_cmd[c_of_s - 1].fd[0]);
	}
	if (g_struct.number_of_pipes > 1)
	{
		close(g_struct.each_cmd[c_of_s].fd[0]);
		dup2(g_struct.each_cmd[c_of_s].fd[1], STDOUT_FILENO);
		close(g_struct.each_cmd[c_of_s].fd[1]);
	}
	if (g_struct.each_cmd[c_of_s].files)
		check_rediractions(c_of_s);
}
