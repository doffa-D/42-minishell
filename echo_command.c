/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:00:54 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/04/21 17:32:26 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_command(t_all *my_struct, int c_of_s)
{
	int		i;
	int		j;

	j = 0;
	i = 1;
	while (my_struct->each_cmd[c_of_s].cmd[i])
	{
		if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[i], "-n",
				ft_strlen("-n") + 1))
		{
			j = 1;
			i++;
		}
		if (ft_strncmp(my_struct->each_cmd[c_of_s].cmd[i], "-n",
				ft_strlen("-n") + 1))
			printf("%s", my_struct->each_cmd[c_of_s].cmd[i]);
		if (j == 0)
			printf("\n");
		i++;
	}
	if (!my_struct->each_cmd[c_of_s].cmd[1])
		printf("\n");
}
