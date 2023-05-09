/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_in_chiled.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:40:28 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 00:29:07 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	some_builtins(int c_of_s)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd",
			ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
	{
		if (cd_commade(c_of_s))
			exit(1);
		exit(0);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0] \
	&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "echo", \
	ft_strlen("echo") + 1))
	{
		echo_command(c_of_s);
		exit(0);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0] \
	&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "pwd", ft_strlen("pwd")
			+ 1))
	{
		pwd_command();
		exit(0);
	}
}

void	another_builtins(int c_of_s)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export",
			ft_strlen("export") + 1))
	{
		g_struct.check = 0;
		export_command(c_of_s);
		if (g_struct.check == 1)
			exit(1);
		exit(0);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")
			+ 1))
	{
		env_command(g_struct.list);
		exit(0);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset",
			ft_strlen("unset") + 1))
	{
		unset_command(c_of_s);
		exit(0);
	}
}

int	builtins(int c_of_s)
{
	some_builtins(c_of_s);
	another_builtins(c_of_s);
	if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit",
			ft_strlen("exit")))
		_exit(c_of_s);
	return (0);
}
