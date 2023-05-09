/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_rediractions_parent_2.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:08:38 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/09 21:25:59 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	input_rediraction(int c_of_s, int j)
{
	int	fd;

	fd = open(g_struct.each_cmd[c_of_s].files[j].files, O_RDWR, 0777);
	if (access(g_struct.each_cmd[c_of_s].files[j].files, R_OK) != 0)
	{
		j = fork();
		error_fork(j);
		if (j == 0)
		{
			dup2(2, 1);
			printf("minishell: %s: Permission denied\n",
				g_struct.each_cmd[c_of_s].files[j].files);
			exit(1);
		}
		return (1);
	}
	fd_error(fd);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	append_rediraction(int c_of_s, int j)
{
	int	fd;

	if (error_in_output_and_append(c_of_s, j))
		return (1);
	fd = open(g_struct.each_cmd[c_of_s].files[j].files, \
			O_CREAT | O_RDWR | O_APPEND, 0777);
	if (access(g_struct.each_cmd[c_of_s].files[j].files, W_OK) != 0)
	{
		j = fork();
		error_fork(j);
		if (j == 0)
		{
			dup2(2, 1);
			printf("minishell: %s: Permission denied\n",
				g_struct.each_cmd[c_of_s].files[j].files);
			exit(1);
		}
		return (1);
	}
	fd_error(fd);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	_all_rediraction(int c_of_s, int j)
{
	if (error_rediraction(c_of_s, j))
		return (1);
	if (g_struct.each_cmd[c_of_s].files[j].output == 1)
	{
		if (output_rediraction(c_of_s, j))
			return (1);
	}
	if (g_struct.each_cmd[c_of_s].files[j].input == 1)
	{
		if (input_rediraction(c_of_s, j))
			return (1);
	}
	if (g_struct.each_cmd[c_of_s].files[j].append == 1)
		if (append_rediraction(c_of_s, j))
			return (1);
	if (g_struct.each_cmd[c_of_s].files[j].herdoc == 1)
	{
		dup2(g_struct.fils_descreprot, STDIN_FILENO);
		close(g_struct.fils_descreprot);
	}
	return (0);
}

int	check_rediractions_in_parent(int c_of_s)
{
	int	j;

	j = 0;
	while (g_struct.each_cmd[c_of_s].files[j].files)
	{
		_all_rediraction(c_of_s, j);
		j++;
	}
	if (!g_struct.each_cmd[c_of_s].cmd[0])
		return (-1);
	return (0);
}
