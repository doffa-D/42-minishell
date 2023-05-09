/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rediraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:18:08 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 01:28:06 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

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

int	input_rediraction(int c_of_s, int j)
{
	int	fd;

	fd = open(g_struct.each_cmd[c_of_s].files[j].files, O_RDWR, 0777);
	if (access(g_struct.each_cmd[c_of_s].files[j].files, R_OK) != 0)
	{
		j = fork();
		if (j == 0)
		{
			dup2(2, 1);
			printf("minishell: %s: Permission denied\n",
				g_struct.each_cmd[c_of_s].files[j].files);
			exit(1);
		}
		return (1);
	}
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
		if (j == 0)
		{
			dup2(2, 1);
			printf("minishell: %s: Permission denied\n",
				g_struct.each_cmd[c_of_s].files[j].files);
			exit(1);
		}
		return (1);
	}
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

void	check_rediractions(int c_of_s)
{
	int	j;

	j = 0;
	while (g_struct.each_cmd[c_of_s].files[j].files)
	{
		_error_rediraction_in_chiled(c_of_s, j);
		if (g_struct.each_cmd[c_of_s].files[j].output == 1)
			_rediraction_output_in_chiled(c_of_s, j);
		else if (g_struct.each_cmd[c_of_s].files[j].input == 1)
			_rediraction_input_in_chiled(c_of_s, j);
		if (g_struct.each_cmd[c_of_s].files[j].append == 1)
			_rediraction_append_in_chiled(c_of_s, j);
		else if (g_struct.each_cmd[c_of_s].files[j].herdoc == 1)
		{
			dup2(g_struct.fils_descreprot, STDIN_FILENO);
			close(g_struct.fils_descreprot);
		}
		j++;
	}
	if (!g_struct.each_cmd[c_of_s].cmd[0])
		exit(0);
}
