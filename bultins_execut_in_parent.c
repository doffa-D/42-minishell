/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins_execut_in_parent.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:39:41 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 13:39:51 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	some_builtins_in_parent(int c_of_s)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd",
			ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
	{
		if (cd_commade(c_of_s))
			return (-1);
		return (1);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export",
			ft_strlen("export") + 1))
	{
		g_struct.check = 0;
		export_command(c_of_s);
		if (g_struct.check == 1)
			return (-1);
		return (1);
	}
	return (0);
}

int	builtins_in_parent(int c_of_s)
{
	int	i;

	i = some_builtins_in_parent(c_of_s);
	if (i != 0)
		return (i);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")
			+ 1))
	{
		env_command(g_struct.list);
		return (1);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset",
			ft_strlen("unset") + 1))
	{
		if (unset_command(c_of_s))
			return (-1);
		return (1);
	}
	if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit",
			ft_strlen("exit")))
		_exit(c_of_s);
	return (0);
}