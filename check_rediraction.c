/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rediraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:18:08 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/07 22:59:14 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>


// void	handler_herdoc(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		signal(SIGINT, &handler);
// 		exit(0);
// 	}
// }

int	check_rediractions_in_parent(int c_of_s)
{
	int j = 0;
	while (g_struct.each_cmd[c_of_s].files[j].files)
	{
		if(g_struct.each_cmd[c_of_s].files[j].ambiguous == 1)
		{
			j = fork();
			if(j == 0)
			{
				dup2(2, 1);
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				exit(1);
			}
			return 1;
		}
		if(!*g_struct.each_cmd[c_of_s].files[j].files)
		{
			j = fork();
			if(j == 0)
			{
				dup2(2, 1);
				printf("minishell: %s: No such file or directory\n", g_struct.each_cmd[c_of_s].files[j].files);
				exit(1);
			}
			return 1;
		}
		if (g_struct.each_cmd[c_of_s].files[j].OUTPUT == 1)
		{
			if(ft_strchr(g_struct.each_cmd[c_of_s].files[j].files, '/'))
			{
				j = fork();
				if(j == 0)
				{
					dup2(2, 1);
					printf("minishell: %s: No such file or directory\n", g_struct.each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				return 1;
			}
			int fd = open(g_struct.each_cmd[c_of_s].files[j].files, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if(access(g_struct.each_cmd[c_of_s].files[j].files, W_OK) != 0)
			{
				j = fork();
				if(j == 0)
				{
					dup2(2, 1);
					printf("minishell: %s: Permission denied\n", g_struct.each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				return 1;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (g_struct.each_cmd[c_of_s].files[j].INPUT == 1)
		{
			if(access(g_struct.each_cmd[c_of_s].files[j].files, F_OK) != 0)
			{
				j = fork();
				if(j == 0)
				{
					dup2(2, 1);
					printf("minishell: %s: No such file or directory\n", g_struct.each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				return 1;
			}
			int fd = open(g_struct.each_cmd[c_of_s].files[j].files, O_RDWR , 0777);
			if(access(g_struct.each_cmd[c_of_s].files[j].files, R_OK) != 0)
			{
				j = fork();
				if(j == 0)
				{
					dup2(2, 1);
					printf("minishell: %s: Permission denied\n", g_struct.each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				return 1;
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (g_struct.each_cmd[c_of_s].files[j].APPEND == 1)
		{
			if(ft_strchr(g_struct.each_cmd[c_of_s].files[j].files, '/'))
			{
				j = fork();
				if(j == 0)
				{
					dup2(2, 1);
					printf("minishell: %s: No such file or directory\n", g_struct.each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				return 1;
			}
			int fd = open(g_struct.each_cmd[c_of_s].files[j].files,
					O_CREAT | O_RDWR | O_APPEND, 0777);
			if(access(g_struct.each_cmd[c_of_s].files[j].files, W_OK) != 0)
			{
				j = fork();
				if(j == 0)
				{
					dup2(2, 1);
					printf("minishell: %s: Permission denied\n", g_struct.each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				return 1;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (g_struct.each_cmd[c_of_s].files[j].HERDOC == 1)
		{
			dup2(g_struct.fils_descreprot, STDIN_FILENO);
			close(g_struct.fils_descreprot);
		}
		j++;
	}
	if(!g_struct.each_cmd[c_of_s].cmd[0])
		return -1;
	return 0;
}

int	check_rediractions(int c_of_s)
{
	int j = 0;
	int returnv = 0;
	while (g_struct.each_cmd[c_of_s].files[j].files)
	{
		if(g_struct.each_cmd[c_of_s].files[j].ambiguous == 1)
		{
			dup2(2, 1);
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			exit(1);
		}
		if(!*g_struct.each_cmd[c_of_s].files[j].files)
		{
			dup2(2, 1);
			printf("minishell: %s: No such file or directory\n", g_struct.each_cmd[c_of_s].files[j].files);
			exit(1);
		}
		if (g_struct.each_cmd[c_of_s].files[j].OUTPUT == 1)
		{
			if(ft_strchr(g_struct.each_cmd[c_of_s].files[j].files, '/'))
			{
				dup2(2, 1);
				printf("minishell: %s: No such file or directory\n", g_struct.each_cmd[c_of_s].files[j].files);
				exit(1);
			}
			int fd = open(g_struct.each_cmd[c_of_s].files[j].files, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if(access(g_struct.each_cmd[c_of_s].files[j].files, W_OK) != 0)
			{
				dup2(2, 1);
				printf("minishell: %s: Permission denied\n", g_struct.each_cmd[c_of_s].files[j].files);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			returnv = 1;
		}
		else if (g_struct.each_cmd[c_of_s].files[j].INPUT == 1)
		{
			if(access(g_struct.each_cmd[c_of_s].files[j].files, F_OK) != 0)
			{
				dup2(2, 1);
				printf("minishell: %s: No such file or directory\n", g_struct.each_cmd[c_of_s].files[j].files);
				exit(1);
			}
			int fd = open(g_struct.each_cmd[c_of_s].files[j].files, O_RDWR , 0777);
			if(access(g_struct.each_cmd[c_of_s].files[j].files, R_OK) != 0)
			{
				dup2(2, 1);
				printf("minishell: %s: Permission denied\n", g_struct.each_cmd[c_of_s].files[j].files);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			returnv = 2;
		}
		if (g_struct.each_cmd[c_of_s].files[j].APPEND == 1)
		{
			if(ft_strchr(g_struct.each_cmd[c_of_s].files[j].files, '/'))
			{
				dup2(2, 1);
				printf("minishell: %s: No such file or directory\n", g_struct.each_cmd[c_of_s].files[j].files);
				exit(1);
			}
			int fd = open(g_struct.each_cmd[c_of_s].files[j].files,
					O_CREAT | O_RDWR | O_APPEND, 0777);
			if(access(g_struct.each_cmd[c_of_s].files[j].files, W_OK) != 0)
			{
				dup2(2, 1);
				printf("minishell: %s: Permission denied\n", g_struct.each_cmd[c_of_s].files[j].files);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			returnv = 1;
		}
		else if (g_struct.each_cmd[c_of_s].files[j].HERDOC == 1)
		{
			dup2(g_struct.fils_descreprot, STDIN_FILENO);
			close(g_struct.fils_descreprot);
		}
		j++;
	}
	if(!g_struct.each_cmd[c_of_s].cmd[0])
		exit(0);
	return returnv;
}