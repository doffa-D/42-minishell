/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_rediractions_parent.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:08:38 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/09 23:49:38 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handler_herdoc(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, &handler);
		exit(0);
	}
}

void	error_fork(int pid, int free_or_not)
{
	if (pid == -1)
	{
		perror("fork");
		if (free_or_not)
			free_all_v2(0);
		free_linked_list();
		exit(1);
	}
}

int	error_in_output_and_append(int c_of_s, int j)
{
	if (ft_strchr(g_struct.each_cmd[c_of_s].files[j].files, '/'))
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
		error_fork(j, 1);
		if (j == 0)
		{
			dup2(2, 1);
			printf("minishell: %s: Permission denied\n", \
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

int	error_in_input(int c_of_s, int j)
{
	if (access(g_struct.each_cmd[c_of_s].files[j].files, F_OK) != 0)
	{
		j = fork();
		error_fork(j, 1);
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
