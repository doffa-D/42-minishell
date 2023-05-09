/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_is_exist_or_not.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:27:59 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 15:42:28 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	path_doase_not_exist(int c_of_s)
{
	if (!g_struct.my_path[0] && !if_builtins_in_chiled(c_of_s))
	{
		dup2(2, 1);
		printf("minishell: %s: No such file or directory\n",
			g_struct.each_cmd[c_of_s].cmd[0]);
		exit(127);
	}
}

int	path_is_exist(int c_of_s, int j)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& access(g_struct.each_cmd[c_of_s].cmd[0], F_OK) == 0)
	{
		if (access(g_struct.each_cmd[c_of_s].cmd[0], X_OK) == 0)
			j = 1;
		else
		{
			printf("minishell: %s: Permission denied\n",
				g_struct.each_cmd[c_of_s].cmd[0]);
			exit(126);
		}
	}
	return (j);
}

int	join_path_whit_commade(int c_of_s, int j, int *i)
{
	*i = 0;
	while (g_struct.my_path && g_struct.my_path[*i])
	{
		if (access(g_struct.my_path[*i], F_OK) == 0)
		{
			if (access(g_struct.my_path[*i], X_OK) == 0)
			{
				j = 1;
				break ;
			}
			else
			{
				printf("minishell: %s: Permission denied\n",
					g_struct.each_cmd[c_of_s].cmd[0]);
				exit(126);
			}
		}
		(*i)++;
	}
	return (j);
}
