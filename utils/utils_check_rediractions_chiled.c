/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_rediractions_chiled.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:08:38 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/09 13:27:00 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"

void	_error_rediraction_in_chiled(int c_of_s, int j)
{
	if (g_struct.each_cmd[c_of_s].files[j].ambiguous == 1)
	{
		dup2(2, 1);
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		exit(1);
	}
	if (!*g_struct.each_cmd[c_of_s].files[j].files)
	{
		dup2(2, 1);
		printf("minishell: %s: No such file or directory\n",
			g_struct.each_cmd[c_of_s].files[j].files);
		exit(1);
	}
}

void	_rediraction_output_in_chiled(int c_of_s, int j)
{
	int	fd;

	if (ft_strchr(g_struct.each_cmd[c_of_s].files[j].files, '/'))
	{
		dup2(2, 1);
		printf("minishell: %s: No such file or directory\n",
			g_struct.each_cmd[c_of_s].files[j].files);
		exit(1);
	}
	fd = open(g_struct.each_cmd[c_of_s].files[j].files, \
		O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (access(g_struct.each_cmd[c_of_s].files[j].files, W_OK) != 0)
	{
		dup2(2, 1);
		printf("minishell: %s: Permission denied\n",
			g_struct.each_cmd[c_of_s].files[j].files);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	_rediraction_input_in_chiled(int c_of_s, int j)
{
	int	fd;

	if (access(g_struct.each_cmd[c_of_s].files[j].files, F_OK) != 0)
	{
		dup2(2, 1);
		printf("minishell: %s: No such file or directory\n",
			g_struct.each_cmd[c_of_s].files[j].files);
		exit(1);
	}
	fd = open(g_struct.each_cmd[c_of_s].files[j].files, O_RDWR, 0777);
	if (access(g_struct.each_cmd[c_of_s].files[j].files, R_OK) != 0)
	{
		dup2(2, 1);
		printf("minishell: %s: Permission denied\n",
			g_struct.each_cmd[c_of_s].files[j].files);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	_rediraction_append_in_chiled(int c_of_s, int j)
{
	int	fd;

	if (ft_strchr(g_struct.each_cmd[c_of_s].files[j].files, '/'))
	{
		dup2(2, 1);
		printf("minishell: %s: No such file or directory\n", \
			g_struct.each_cmd[c_of_s].files[j].files);
		exit(1);
	}
	fd = open(g_struct.each_cmd[c_of_s].files[j].files, \
		O_CREAT | O_RDWR | O_APPEND, 0777);
	if (access(g_struct.each_cmd[c_of_s].files[j].files, W_OK) != 0)
	{
		dup2(2, 1);
		printf("minishell: %s: Permission denied\n",
			g_struct.each_cmd[c_of_s].files[j].files);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}