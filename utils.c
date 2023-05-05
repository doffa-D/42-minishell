/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:20:11 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/05 19:26:48 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_the_path(t_all *my_struct, int c_of_s)
{
	int	i;

	i = 0;
	while (my_struct->my_path && my_struct->my_path[i])
	{
		if (my_struct->each_cmd[c_of_s].cmd
			&& my_struct->each_cmd[c_of_s].cmd[0]
			&& *my_struct->each_cmd[c_of_s].cmd[0])
		{
			my_struct->my_path[i] = ft_strjoin(my_struct->my_path[i], "/");
			my_struct->my_path[i] = ft_strjoin(my_struct->my_path[i],
					my_struct->each_cmd[c_of_s].cmd[0]);
			i++;
		}
		else
			return (1);
	}
	return (0);
}
