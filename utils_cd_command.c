/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:52:51 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/09 13:10:15 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_only_cd(int pid, int c_of_s)
{
	char	*cd_path;

	cd_path = my_getenv(g_struct.list, "HOME", 0);
	if (chdir(cd_path) == -1)
	{
		free(cd_path);
		pid = fork();
		if (pid == 0)
		{
			dup2(2, 1);
			printf("minishell: %s: HOME not set\n",
				g_struct.each_cmd[c_of_s].cmd[0]);
			exit(1);
		}
		wait(&pid);
		return (1);
	}
	free(cd_path);
	return (0);
}

int	_cd_whith_tilde(int c_of_s, int pid)
{
	char	*str;

	str = ft_strjoin(my_getenv(g_struct.list, "HOME", 0), \
		&g_struct.each_cmd[c_of_s].cmd[1][1]);
	if (chdir(str) == -1)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(2, 1);
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			exit(1);
		}
		wait(&pid);
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

int	_cd_whith_somthing(int c_of_s, int pid)
{
	if (g_struct.each_cmd[c_of_s].cmd[1]
		&& chdir(g_struct.each_cmd[c_of_s].cmd[1]) == -1)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(2, 1);
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			exit(1);
		}
		wait(&pid);
		return (1);
	}
	return (0);
}

int	_cd_whith_slash(int c_of_s, int pid)
{
	if (g_struct.each_cmd[c_of_s].cmd[1]
		&& chdir(g_struct.each_cmd[c_of_s].cmd[1]) == -1)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(2, 1);
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			exit(1);
		}
		wait(&pid);
		return (1);
	}
	return (0);
}

int	_cd(int c_of_s, int pid)
{
	if (ft_strlen(g_struct.each_cmd[c_of_s].cmd[0]) == 2
		&& !g_struct.each_cmd[c_of_s].cmd[1])
	{
		if (_only_cd(pid, c_of_s))
			return (1);
	}
	else if (_cd_whith_somthing(c_of_s, pid))
		return (1);
	return (0);
}
