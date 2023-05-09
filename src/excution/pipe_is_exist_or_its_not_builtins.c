/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_is_exist_or_its_not_builtins.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:29:51 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 23:38:36 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipe_is_exist_or_its_not_builtins(int c_of_s, int i)
{
	int	*pid;

	c_of_s = 0;
	pid = malloc(g_struct.number_of_pipes * sizeof(int));
	while (g_struct.number_of_pipes > 0)
	{
		i = fork();
			// signal(SIGINT, SIG_IGN);//ask_about_it
		error_fork(i, 1);
		if (i == 0)
			check_error_and_excute_comande(c_of_s);
		else
			pid[c_of_s] = i;
		if (g_struct.number_of_pipes > 1)
			close(g_struct.each_cmd[c_of_s].fd[1]);
		g_struct.number_of_pipes--;
		c_of_s++;
	}
	// signal(SIGINT, &handler);
	wait_and_close_all(c_of_s, pid);
	free(pid);
}

void	check_error_and_excute_comande(int c_of_s)
{
	int	j;
	int	i;

	path_doase_not_exist(c_of_s);
	handel_pipe_and_rederaction(c_of_s);
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
