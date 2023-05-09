/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:27:07 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 15:42:28 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_in_commande(int c_of_s)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& (!ft_strchr(g_struct.each_cmd[c_of_s].cmd[0], '/')))
	{
		dup2(2, 1);
		printf("minishell: %s: command not found\n",
			g_struct.each_cmd[c_of_s].cmd[0]);
		exit(127);
	}
}

void	error_is_exist(int c_of_s)
{
	error_in_commande(c_of_s);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& ft_strchr(g_struct.each_cmd[c_of_s].cmd[0], '/'))
	{
		if (!chdir(g_struct.each_cmd[c_of_s].cmd[0]))
		{
			dup2(2, 1);
			printf("minishell: %s: Is a directory\n",
				g_struct.each_cmd[c_of_s].cmd[0]);
			exit(126);
		}
		else
		{
			dup2(2, 1);
			printf("minishell: %s: No such file or directory\n",
				g_struct.each_cmd[c_of_s].cmd[0]);
			exit(127);
		}
	}
}
