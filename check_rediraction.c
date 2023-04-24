/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rediraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:18:08 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/24 15:21:14 by hdagdagu         ###   ########.fr       */
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

void	check_rediractions(t_all *my_struct, int c_of_s)
{
	int j = 0;
	// signal(SIGINT, &handler_herdoc);
	while (my_struct->each_cmd[c_of_s].files[j].files && *my_struct->each_cmd[c_of_s].files[j].files)
	{
		if (my_struct->each_cmd[c_of_s].files[j].OUTPUT == 1)
		{
			int fd = open(my_struct->each_cmd[c_of_s].files[j].files,
					O_CREAT | O_RDWR | O_TRUNC, 0777);
			if(my_struct->each_cmd[c_of_s].cmd && my_struct->each_cmd[c_of_s].cmd[0])
			{
				printf("ddddddd\n");
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}
		else if (my_struct->each_cmd[c_of_s].files[j].INPUT == 1 \
		&& my_struct->each_cmd[c_of_s].cmd)
		{
			int fd = open(my_struct->each_cmd[c_of_s].files[j].files,
					O_RDWR , 0777);
			if(fd == -1)
			{
				perror("error");
				exit(1);
			}
			if(my_struct->each_cmd[c_of_s].cmd && my_struct->each_cmd[c_of_s].cmd[0])
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
		}
		else if (my_struct->each_cmd[c_of_s].files[j].APPEND == 1 \
		&& my_struct->each_cmd[c_of_s].cmd)
		{
			int fd = open(my_struct->each_cmd[c_of_s].files[j].files,
					O_CREAT | O_RDWR | O_APPEND, 0777);
			if(my_struct->each_cmd[c_of_s].cmd && my_struct->each_cmd[c_of_s].cmd[0])
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}
		else if (my_struct->each_cmd[c_of_s].files[j].HERDOC == 1 \
		&& my_struct->each_cmd[c_of_s].cmd)
		{
			int file_origin = dup(STDIN_FILENO);
			int fd_by_pipe[2];
			char *beffer = 0;
			char *herdoc = ft_strdup("");
			pipe(fd_by_pipe);
			while (1)
			{
				beffer = readline("> ");
				if(!beffer)
					break;
				if (!ft_strncmp(beffer,
						my_struct->each_cmd[c_of_s].files[j].files,
						ft_strlen(my_struct->each_cmd[c_of_s].files[j].files)) \
						&& !ft_strncmp(beffer, my_struct->each_cmd[c_of_s].files[j].files,
						ft_strlen(beffer)))
					break ;
				herdoc = ft_strjoin(herdoc, beffer);
				herdoc = ft_strjoin(herdoc, "\n");
			}
			ft_putstr_fd(herdoc, fd_by_pipe[1]);
			close(fd_by_pipe[1]);
			free(herdoc);
			dup2(fd_by_pipe[0], STDIN_FILENO);
			close(fd_by_pipe[0]);
			if (my_struct->each_cmd[c_of_s].files[j + 1].HERDOC == 1)
				dup2(file_origin, STDIN_FILENO);
			close(file_origin);
		}
		j++;
	}
	// signal(SIGINT, &handler);
}