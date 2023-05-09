/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit_commande.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:42:37 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 12:06:04 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	utils_of_exit(int c_of_s, long long i)
{
	while (g_struct.each_cmd[c_of_s].cmd[1][i])
	{
		if (!ft_isdigit(g_struct.each_cmd[c_of_s].cmd[1][i]))
		{
			dup2(2, 1);
			printf("minishell: exit: %s: numeric argument required\n",
				g_struct.each_cmd[c_of_s].cmd[1]);
			free_commande_whit_out_path(0, 0);
			exit(255);
		}
		i++;
	}
	if (!g_struct.each_cmd[c_of_s].cmd[2])
	{
		i = ft_atoi(g_struct.each_cmd[c_of_s].cmd[1]);
		free_commande_whit_out_path(0, 0);
		exit(i);
	}
}

void	exit_error_not_numeric(int c_of_s, long long i)
{
	if (g_struct.each_cmd[c_of_s].cmd[1])
	{
		if (!ft_isdigit(g_struct.each_cmd[c_of_s].cmd[1][i])
			&& g_struct.each_cmd[c_of_s].cmd[1][i] != '-'
			&& g_struct.each_cmd[c_of_s].cmd[1][i] != '+')
		{
			dup2(2, 1);
			printf("minishell: exit: %s: numeric argument required\n",
				g_struct.each_cmd[c_of_s].cmd[1]);
			free_commande_whit_out_path(0, 0);
			exit(255);
		}
		i++;
		utils_of_exit(c_of_s, i);
	}
}
