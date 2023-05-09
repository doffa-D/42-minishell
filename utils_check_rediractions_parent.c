/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_rediractions_parent.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:08:38 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/09 12:09:58 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handler_herdoc(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, &handler);
		exit(0);
	}
}

int	error_rediraction(int c_of_s, int j)
{
	if (g_struct.each_cmd[c_of_s].files[j].ambiguous == 1)
	{
		j = fork();
		if (j == 0)
		{
			dup2(2, 1);
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			exit(1);
		}
		return (1);
	}
	if (!*g_struct.each_cmd[c_of_s].files[j].files)
	{
		j = fork();
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

int	error_in_output_and_append(int c_of_s, int j)
{
	if (ft_strchr(g_struct.each_cmd[c_of_s].files[j].files, '/'))
	{
		j = fork();
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

int	output_rediraction(int c_of_s, int j)
{
	int	fd;

	if (error_in_output_and_append(c_of_s, j))
		return (1);
	fd = open(g_struct.each_cmd[c_of_s].files[j].files, \
		O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (access(g_struct.each_cmd[c_of_s].files[j].files, W_OK) != 0)
	{
		j = fork();
		if (j == 0)
		{
			dup2(2, 1);
			printf("minishell: %s: Permission denied\n", \
					g_struct.each_cmd[c_of_s].files[j].files);
			exit(1);
		}
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	error_in_input(int c_of_s, int j)
{
	if (access(g_struct.each_cmd[c_of_s].files[j].files, F_OK) != 0)
	{
		j = fork();
		if (j == 0)
		{
			dup2(2, 1);
			printf("minishell: %s: No such file or directory\n",
				g_struct.each_cmd[c_of_s].files[j].files);
			exit(1);
		}
		return (1);
	}
	return (0);
}
