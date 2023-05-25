/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:08:08 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/13 00:41:07 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_each_cmd(int i, int j)
{
	while (g_struct.each_cmd[i].files || g_struct.each_cmd[i].cmd)
	{
		j = 0;
		if (g_struct.each_cmd[i].files)
		{
			j = 0;
			while (g_struct.each_cmd[i].files[j].files)
			{
				free(g_struct.each_cmd[i].files[j].files);
				j++;
			}
			free(g_struct.each_cmd[i].files);
		}
		if (g_struct.each_cmd[i].cmd)
		{
			j = 0;
			while (g_struct.each_cmd[i].cmd[j])
			{
				free(g_struct.each_cmd[i].cmd[j]);
				j++;
			}
			free(g_struct.each_cmd[i].cmd);
		}
		i++;
	}
}

void	syntax_error(t_var *variables)
{
	int	i;

	i = fork();
	error_fork(i, 0);
	if (i == 0)
	{
		ft_putstr_fd("minishell: syntax error rederaction\n", 2);
		exit(1);
	}
	wait(&i);
	free_each_cmd(0, 0);
	free(g_struct.each_cmd);
	free(g_struct.tmp_cmd);
	free(g_struct.the_commande);
	while (g_struct.splite_pipe[variables->index_i])
	{
		free(g_struct.splite_pipe[variables->index_i]);
		variables->index_i++;
	}
	free(g_struct.splite_pipe);
}
