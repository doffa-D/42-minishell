/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rediraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:18:08 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/01 00:28:31 by nouakhro         ###   ########.fr       */
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

int	check_rediractions(t_all *my_struct, int c_of_s)
{
	int j = 0;
	int returnv = 0;
	// signal(SIGINT, &handler_herdoc);
		while (my_struct->each_cmd[c_of_s].files[j].files)
		{
			if(!*my_struct->each_cmd[c_of_s].files[j].files)
			{
				dup2(2, 1);
				printf("minishell: %s: No such file or directory\n", my_struct->each_cmd[c_of_s].files[j].files);
				exit(1);
			}
			if (my_struct->each_cmd[c_of_s].files[j].OUTPUT == 1)
			{
				int fd = open(my_struct->each_cmd[c_of_s].files[j].files, O_CREAT | O_RDWR | O_TRUNC, 0777);
				if(access(my_struct->each_cmd[c_of_s].files[j].files, W_OK) != 0)
				{
					dup2(2, 1);
					printf("minishell: %s: Permission denied\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				if(my_struct->each_cmd[c_of_s].cmd[0])
				{
					dup2(fd, STDOUT_FILENO);
					close(fd);
				}
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
				if(my_struct->each_cmd[c_of_s].cmd[0])
				{
					dup2(fd, STDIN_FILENO);
					close(fd);
				}
				returnv = 2;
			}
			// printf("%s\n", my_struct->each_cmd[c_of_s].files[j].files);
			if (my_struct->each_cmd[c_of_s].files[j].APPEND == 1)
			{
				int fd = open(my_struct->each_cmd[c_of_s].files[j].files,
						O_CREAT | O_RDWR | O_APPEND, 0777);
				if(access(my_struct->each_cmd[c_of_s].files[j].files, W_OK) != 0)
				{
					dup2(2, 1);
					printf("minishell: %s: Permission denied\n", my_struct->each_cmd[c_of_s].files[j].files);
					exit(1);
				}
				if(my_struct->each_cmd[c_of_s].cmd[0])
				{
					dup2(fd, STDOUT_FILENO);
					close(fd);
				}
				returnv = 1;
			}
			else if (my_struct->each_cmd[c_of_s].files[j].HERDOC == 1)
			{
				int file_origin = dup(STDIN_FILENO);
				int fd_by_pipe[2];
				char *buffer = 0;
				char *buffer_tmp = 0;
				char *herdoc = ft_strdup("");
				int i = 0;
				int c = 0;
				pipe(fd_by_pipe);
				while (1)
				{
					buffer = readline("> ");
					if(!buffer)
						break;
					if (!ft_strncmp(buffer, my_struct->each_cmd[c_of_s].files[j].files,
							ft_strlen(buffer) + 1))
						break ;
					if(ft_strchr(buffer, '$') && my_struct->each_cmd[c_of_s].files[j].HERDOC_OPTION == 0)
					{
						i = 0;
						c = 0;
						while (buffer[i])
						{
							if((buffer[i] == '$' \
								&& buffer[i + 1] \
								&& buffer[i + 1] != ' '))
							{
								herdoc = ft_strjoin_v2(herdoc, ft_substr(buffer, c, i - c));
								i++;
								if(buffer[i] == '?')
								{
									herdoc = ft_strjoin_v2(herdoc, ft_itoa(my_struct->exit_status));
									i++;
									c = i;
								}
								else
								{
									while (ft_isalnum(buffer[i]))
										i++;
									buffer_tmp = ft_substr(buffer, c, i - c);
									herdoc = ft_strjoin_v2(herdoc, my_getenv(my_struct->list, buffer_tmp));
									free(buffer_tmp);
									c = i;
								}
								i--;
							}
							if(!buffer[i])
								break;
							i++;
						}
						herdoc = ft_strjoin_v2(herdoc, ft_substr(buffer, c, i - c));
					}
					else
						herdoc = ft_strjoin(herdoc, buffer);
					herdoc = ft_strjoin(herdoc, "\n");
				}
				if(my_struct->each_cmd[c_of_s].cmd[0])
				{
					ft_putstr_fd(herdoc, fd_by_pipe[1]);
					close(fd_by_pipe[1]);
					free(herdoc);
					dup2(fd_by_pipe[0], STDIN_FILENO);
					close(fd_by_pipe[0]);
					if (my_struct->each_cmd[c_of_s].files[j + 1].HERDOC == 1)
						dup2(file_origin, STDIN_FILENO);
					close(file_origin);
					returnv = 2;
				}
			}
			j++;
		}
	// signal(SIGINT, &handler);
	return returnv;
}