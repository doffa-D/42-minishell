/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_is_exist_or_its_not_builtins.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:29:51 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/13 21:53:05 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipe_is_exist_or_its_not_builtins(int c_of_s, int i)
{
	int	*pid;
	int	number_of_pipe;

	number_of_pipe = g_struct.number_of_pipes;
	c_of_s = 0;
	pid = malloc(g_struct.number_of_pipes * sizeof(int));
	while (g_struct.number_of_pipes > 0)
	{
		signal(SIGINT, SIG_IGN);
		i = fork();
		error_fork(i, 1);
		if (i == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			check_error_and_excute_comande(c_of_s, number_of_pipe);
		}
		else
			pid[c_of_s] = i;
		g_struct.number_of_pipes--;
		c_of_s++;
	}
	wait_and_close_all(c_of_s, pid);
	signal(SIGINT, &handler);
	free(pid);
}

void	check_error_and_excute_comande(int c_of_s, int number_of_pipe)
{
	int	j;
	int	i;

	path_doase_not_exist(c_of_s);
	handel_pipe_and_rederaction(c_of_s);
	j = 0;
	while (j < number_of_pipe - 1)
	{
		close(g_struct.each_cmd[j].fd[1]);
		close(g_struct.each_cmd[j].fd[0]);
		j++;
	}
	j = builtins(c_of_s);
	j = 0;
	i = 0;
	if (g_struct.each_cmd[c_of_s].cmd[0] \
	&& !ft_strchr(g_struct.each_cmd[c_of_s].cmd[0], '/')
		&& !get_the_path(c_of_s))
		j = join_path_whit_commade(c_of_s, j, &i);
	else
		j = path_is_exist(c_of_s, j);
	if (j != 1)
		error_is_exist(c_of_s);
	else
		exicut_commande(i, c_of_s);
}
