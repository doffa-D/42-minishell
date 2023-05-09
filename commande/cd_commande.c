/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_commande.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:50:10 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 15:22:15 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"

int	cd_commade(int c_of_s)
{
	char	*old;
	int		pid;

	pid = 0;
	old = getcwd(NULL, 255);
	if ((ft_strlen(g_struct.each_cmd[c_of_s].cmd[0]) == 2 \
			&& g_struct.each_cmd[c_of_s].cmd[1] \
			&& (g_struct.each_cmd[c_of_s].cmd[1][0] == '~' \
				|| g_struct.each_cmd[c_of_s].cmd[1][1] == '/')))
	{
		if (g_struct.each_cmd[c_of_s].cmd[1][0] == '~')
		{
			if (_cd_whith_tilde(c_of_s, pid))
				return (1);
		}
		else if (g_struct.each_cmd[c_of_s].cmd[1] \
				&& g_struct.each_cmd[c_of_s].cmd[1][1] == '/')
			if (_cd_whith_slash(c_of_s, pid))
				return (1);
	}
	else if (_cd(c_of_s, pid))
		return (free(old), 1);
	searcher(g_struct.list, old);
	free(old);
	return (0);
}
