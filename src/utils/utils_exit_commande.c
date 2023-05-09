/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit_commande.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:42:37 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 23:58:08 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	manage_exit_error(int c_of_s, long long i, size_t len, char *num)
{
	if (len > ft_strlen(num))
	{
		printf("bash: exit: %s: numeric argument required\n", \
		g_struct.each_cmd[c_of_s].cmd[1]);
		free_commande_whit_out_path(0, 0);
		free(num);
		free_linked_list();
		exit(255);
	}
	if (ft_strncmp(num, &g_struct.each_cmd[c_of_s].cmd[1][i], \
	ft_strlen(num)) < 0 && len == ft_strlen(num))
	{
		printf("bash: exit: %s: numeric argument required\n", \
		g_struct.each_cmd[c_of_s].cmd[1]);
		free_commande_whit_out_path(0, 0);
		free(num);
		free_linked_list();
		exit(255);
	}
}

void	not_2_argemnt(int c_of_s, long long i)
{
	char	*num;
	size_t	len;

	if (!g_struct.each_cmd[c_of_s].cmd[2])
	{
		num = ft_strdup("9223372036854775807");
		i = 0;
		if (g_struct.each_cmd[c_of_s].cmd[1][i] == '+' \
		|| g_struct.each_cmd[c_of_s].cmd[1][i] == '-')
			i++;
		while (g_struct.each_cmd[c_of_s].cmd[1][i] && \
		g_struct.each_cmd[c_of_s].cmd[1][i] == '0')
			i++;
		len = ft_strlen(&g_struct.each_cmd[c_of_s].cmd[1][i]);
		manage_exit_error(c_of_s, i, len, num);
		free(num);
		i = ft_atoi(g_struct.each_cmd[c_of_s].cmd[1]);
		free_commande_whit_out_path(0, 0);
		free_linked_list();
		exit(i);
	}
}

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
			free_linked_list();
			exit(255);
		}
		i++;
	}
	not_2_argemnt(c_of_s, i);
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
