/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:20:11 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 13:27:00 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"

int	get_the_path(int c_of_s)
{
	int	i;

	i = 0;
	while (g_struct.my_path && g_struct.my_path[i])
	{
		if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0]
			&& *g_struct.each_cmd[c_of_s].cmd[0])
		{
			g_struct.my_path[i] = ft_strjoin(g_struct.my_path[i], "/");
			g_struct.my_path[i] = ft_strjoin(g_struct.my_path[i],
					g_struct.each_cmd[c_of_s].cmd[0]);
			i++;
		}
		else
			return (1);
	}
	return (0);
}
