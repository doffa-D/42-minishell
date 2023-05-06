/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_rederaction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 00:42:18 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/06 19:52:40 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
void pipe_and_rederaction(int j, int c_of_s, int **pipe_n)
{
    if(g_struct.each_cmd[c_of_s].files && c_of_s == 0)
		check_rediractions(c_of_s);
	if(c_of_s > 0)
	{
    	close(pipe_n[c_of_s - 1][1]);
		dup2(pipe_n[c_of_s - 1][0], STDIN_FILENO);
    	close(pipe_n[c_of_s - 1][0]);
	}
	if(g_struct.number_of_pipes > 1)
	{
		close(pipe_n[c_of_s][0]);
		dup2(pipe_n[c_of_s][1], STDOUT_FILENO);
		close(pipe_n[c_of_s][1]);
	}
	if(g_struct.each_cmd[c_of_s].files && c_of_s)
		check_rediractions(c_of_s);
	if (g_struct.each_cmd[0].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "echo", ft_strlen("echo")+1))
	{
		echo_command(c_of_s);
		exit(0);
	}
	j = builtins(c_of_s);
	if(j == 1)
		exit(0);
	if(j == -1)
		exit(1);
}