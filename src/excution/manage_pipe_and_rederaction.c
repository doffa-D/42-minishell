/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe_and_rederaction.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:25:43 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/13 19:51:33 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handel_pipe_and_rederaction(int c_of_s)
{
	if (c_of_s > 0)
		dup2(g_struct.each_cmd[c_of_s - 1].fd[0], STDIN_FILENO);
	if (g_struct.number_of_pipes > 1)
		dup2(g_struct.each_cmd[c_of_s].fd[1], STDOUT_FILENO);
	if (g_struct.each_cmd[c_of_s].files)
		check_rediractions(c_of_s);
}
