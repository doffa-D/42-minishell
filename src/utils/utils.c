/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:20:11 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 19:40:30 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_in_chiled_protiction(void)
{
	dup2(2, 1);
	printf("malloc eroor\n");
	exit(1);
}

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
			if (!g_struct.my_path[i])
				exit_in_chiled_protiction();
			g_struct.my_path[i] = ft_strjoin(g_struct.my_path[i],
					g_struct.each_cmd[c_of_s].cmd[0]);
			if (!g_struct.my_path[i])
				exit_in_chiled_protiction();
			i++;
		}
		else
			return (1);
	}
	return (0);
}
