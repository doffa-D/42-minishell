/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:24:18 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 13:24:57 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	wait_and_close_all(int c_of_s, int *pid)
{
	int	i;

	i = 0;
	if(g_struct.fils_descreprot != 0)
		close(g_struct.fils_descreprot);
	while (i < c_of_s - 1)
	{
		close(g_struct.each_cmd[i].fd[1]);
		close(g_struct.each_cmd[i].fd[0]);
		i++;
	}
	i = 0;
	while (i < c_of_s)
	{
		waitpid(pid[i], &g_struct.exit_status, 0);
		if (WIFEXITED(g_struct.exit_status))
			g_struct.exit_status = WEXITSTATUS(g_struct.exit_status);
		else if (WIFSIGNALED(g_struct.exit_status))
			g_struct.exit_status = WTERMSIG(g_struct.exit_status) + 128;
		i++;
	}
}

void	free_commande_whit_out_path(int i, int j)
{
	i = 0;
	j = 0;
	while (g_struct.each_cmd[i].files)
	{
		j = 0;
		while (g_struct.each_cmd[i].files[j].files)
		{
			free(g_struct.each_cmd[i].files[j].files);
			j++;
		}
		free(g_struct.each_cmd[i].files);
		i++;
	}
	i = 0;
	while (g_struct.each_cmd[i].cmd)
	{
		j = 0;
		while (g_struct.each_cmd[i].cmd[j])
		{
			free(g_struct.each_cmd[i].cmd[j]);
			j++;
		}
		free(g_struct.each_cmd[i].cmd);
		i++;
	}
	free(g_struct.each_cmd);
}

void	free_all_v2(int num)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (num == 1)
	{
		while (g_struct.my_path[i])
		{
			free(g_struct.my_path[i]);
			i++;
		}
		free(g_struct.my_path);
	}
	free_commande_whit_out_path(i, j);
}
