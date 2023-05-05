/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_rederaction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 00:42:18 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/05 19:38:42 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pip(int **pipe_n, int c_of_s, int i)
{
	if (i == 0)
	{
		close(pipe_n[c_of_s][1]);
		dup2(pipe_n[c_of_s][0], STDIN_FILENO);
		close(pipe_n[c_of_s][0]);
	}
	else if (i == 1)
	{
		close(pipe_n[c_of_s][0]);
		dup2(pipe_n[c_of_s][1], STDIN_FILENO);
		close(pipe_n[c_of_s][1]);
	}
}

void	pipe_and_rederaction(int j, int c_of_s, t_all *my_struct, int **pipe_n)
{
	if (my_struct->each_cmd[c_of_s].files && c_of_s == 0)
		check_rediractions(my_struct, c_of_s);
	if (c_of_s > 0)
		close_pip(pipe_n, c_of_s - 1, 0);
	if (my_struct->number_of_pipes > 1)
		close_pip(pipe_n, c_of_s, 1);
	if (my_struct->each_cmd[c_of_s].files && c_of_s)
		check_rediractions(my_struct, c_of_s);
	if (my_struct->each_cmd[0].cmd[0]
		&& !ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "echo",
			ft_strlen("echo") + 1))
	{
		echo_command(my_struct, c_of_s);
		exit(0);
	}
	j = builtins(my_struct, c_of_s);
	if (j == 1)
		exit(0);
	if (j == -1)
		exit(1);
}
