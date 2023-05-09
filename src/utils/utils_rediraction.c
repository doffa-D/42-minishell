/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rediraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:01:16 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 23:40:01 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error_rederaction_utils(int c_of_s, int j)
{
	if (!*g_struct.each_cmd[c_of_s].files[j].files)
	{
		j = fork();
		error_fork(j, 1);
		if (j == 0)
		{
			dup2(2, 1);
			printf("minishell: %s: No such file or directory\n", \
					g_struct.each_cmd[c_of_s].files[j].files);
			exit(1);
		}
		return (1);
	}
	return (0);
}

int	error_rediraction(int c_of_s, int j)
{
	if (g_struct.each_cmd[c_of_s].files[j].ambiguous == 1)
	{
		j = fork();
		error_fork(j, 1);
		if (j == 0)
		{
			dup2(2, 1);
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			exit(1);
		}
		return (1);
	}
	return (error_rederaction_utils(c_of_s, j));
}
