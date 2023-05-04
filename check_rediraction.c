/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rediraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:18:08 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/04 13:25:43 by nouakhro         ###   ########.fr       */
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

int	check_rediractions_in_parent(t_all *my_struct, int c_of_s)
{
	int j = 0;
	// signal(SIGINT, &handler_herdoc);
	while (my_struct->each_cmd[c_of_s].files[j].files)
	{
		if(my_struct->each_cmd[c_of_s].files[j].ambiguous == 1)
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
		if(!*my_struct->each_cmd[c_of_s].files[j].files)
		{
			j = fork();
			if(j == 0)
			{
				dup2(2, 1);
				printf("minishell: %s: No such file or directory\n", my_struct->each_cmd[c_of_s].files[j].files);
				exit(1);
			}
			return 1;
		}
		if (my_struct->each_cmd[c_of_s].files[j].OUTPUT == 1)
		{
			if(ft_strchr(my_struct->each_cmd[c_of_s].files[j].files, '/'))
			{
				j = fork();
				if(j == 0)
				{
					dup2(2, 1);
					printf("minishell: %s: No such file or directory\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				return 1;
			}
			int fd = open(my_struct->each_cmd[c_of_s].files[j].files, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if(access(my_struct->each_cmd[c_of_s].files[j].files, W_OK) != 0)
			{
				j = fork();
				if(j == 0)
				{
					dup2(2, 1);
					printf("minishell: %s: Permission denied\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				return 1;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (my_struct->each_cmd[c_of_s].files[j].INPUT == 1)
		{
			if(access(my_struct->each_cmd[c_of_s].files[j].files, F_OK) != 0)
			{
				j = fork();
				if(j == 0)
				{
					dup2(2, 1);
					printf("minishell: %s: No such file or directory\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				return 1;
			}
			int fd = open(my_struct->each_cmd[c_of_s].files[j].files, O_RDWR , 0777);
			if(access(my_struct->each_cmd[c_of_s].files[j].files, R_OK) != 0)
			{
				j = fork();
				if(j == 0)
				{
					dup2(2, 1);
					printf("minishell: %s: Permission denied\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				return 1;
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (my_struct->each_cmd[c_of_s].files[j].APPEND == 1)
		{
			if(ft_strchr(my_struct->each_cmd[c_of_s].files[j].files, '/'))
			{
				j = fork();
				if(j == 0)
				{
					dup2(2, 1);
					printf("minishell: %s: No such file or directory\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				return 1;
			}
			int fd = open(my_struct->each_cmd[c_of_s].files[j].files,
					O_CREAT | O_RDWR | O_APPEND, 0777);
			if(access(my_struct->each_cmd[c_of_s].files[j].files, W_OK) != 0)
			{
				j = fork();
				if(j == 0)
				{
					dup2(2, 1);
					printf("minishell: %s: Permission denied\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				return 1;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (my_struct->each_cmd[c_of_s].files[j].HERDOC == 1)
		{
			dup2(my_struct->fils_descreprot, STDIN_FILENO);
			close(my_struct->fils_descreprot);
		}
		j++;
	}
	if(!my_struct->each_cmd[c_of_s].cmd[0])
		return -1;
	// signal(SIGINT, &handler);
	return 0;
}

int	check_rediractions(t_all *my_struct, int c_of_s)
{
	int j = 0;
	int returnv = 0;
	// signal(SIGINT, &handler_herdoc);
		while (my_struct->each_cmd[c_of_s].files[j].files)
		{
			if(my_struct->each_cmd[c_of_s].files[j].ambiguous == 1)
			{
				dup2(2, 1);
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				exit(1);
			}
			if(!*my_struct->each_cmd[c_of_s].files[j].files)
			{
				dup2(2, 1);
				printf("minishell: %s: No such file or directory\n", my_struct->each_cmd[c_of_s].files[j].files);
				exit(1);
			}
			if (my_struct->each_cmd[c_of_s].files[j].OUTPUT == 1)
			{
				if(ft_strchr(my_struct->each_cmd[c_of_s].files[j].files, '/'))
				{
					dup2(2, 1);
					printf("minishell: %s: No such file or directory\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				int fd = open(my_struct->each_cmd[c_of_s].files[j].files, O_CREAT | O_RDWR | O_TRUNC, 0777);
				if(access(my_struct->each_cmd[c_of_s].files[j].files, W_OK) != 0)
				{
					dup2(2, 1);
					printf("minishell: %s: Permission denied\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
				returnv = 1;
			}
			else if (my_struct->each_cmd[c_of_s].files[j].INPUT == 1)
			{
				if(access(my_struct->each_cmd[c_of_s].files[j].files, F_OK) != 0)
				{
					dup2(2, 1);
					printf("minishell: %s: No such file or directory\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				int fd = open(my_struct->each_cmd[c_of_s].files[j].files, O_RDWR , 0777);
				if(access(my_struct->each_cmd[c_of_s].files[j].files, R_OK) != 0)
				{
					dup2(2, 1);
					printf("minishell: %s: Permission denied\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
				returnv = 2;
			}
			if (my_struct->each_cmd[c_of_s].files[j].APPEND == 1)
			{
				if(ft_strchr(my_struct->each_cmd[c_of_s].files[j].files, '/'))
				{
					dup2(2, 1);
					printf("minishell: %s: No such file or directory\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				int fd = open(my_struct->each_cmd[c_of_s].files[j].files,
						O_CREAT | O_RDWR | O_APPEND, 0777);
				if(access(my_struct->each_cmd[c_of_s].files[j].files, W_OK) != 0)
				{
					dup2(2, 1);
					printf("minishell: %s: Permission denied\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
				returnv = 1;
			}
			else if (my_struct->each_cmd[c_of_s].files[j].HERDOC == 1)
			{
				dup2(my_struct->fils_descreprot, STDIN_FILENO);
				close(my_struct->fils_descreprot);
			}
			j++;
		}
		if(!my_struct->each_cmd[c_of_s].cmd[0])
			exit(0);
	// signal(SIGINT, &handler);
	return returnv;
}