/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_is_exist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:37:40 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 13:38:23 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	if_builtins_in_parent(int c_of_s)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd",
			ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export",
			ft_strlen("export") + 1))
		return (1);
	else if (g_struct.each_cmd[c_of_s].cmd[0]
			&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env",
				ft_strlen("env") + 1))
		return (1);
	else if (g_struct.each_cmd[c_of_s].cmd[0]
			&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset",
				ft_strlen("unset") + 1))
		return (1);
	else if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0]
			&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit",
				ft_strlen("exit")))
		return (1);
	return (0);
}

int	_is_builtins(int c_of_s)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd",
			ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export",
			ft_strlen("export") + 1))
		return (1);
	if (g_struct.each_cmd[0].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "echo",
			ft_strlen("echo") + 1))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "pwd", ft_strlen("pwd")
			+ 1))
		return (1);
	return (0);
}

int	if_builtins_in_chiled(int c_of_s)
{
	if (_is_builtins(c_of_s))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")
			+ 1))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset",
			ft_strlen("unset") + 1))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit",
			ft_strlen("exit")))
		return (1);
	return (0);
}