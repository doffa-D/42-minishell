/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rediraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:18:08 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/19 00:43:44 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	check_rediractions(t_all *my_struct, int c_of_s)
{
	int j = 0;
	while (my_struct->each_cmd[c_of_s].files[j].files)
	{
		if (my_struct->each_cmd[c_of_s].files[j].OUTPUT == 1)
		{
			int fd = open(my_struct->each_cmd[c_of_s].files[j].files,
					O_CREAT | O_RDWR | O_TRUNC, 0777);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (my_struct->each_cmd[c_of_s].files[j].INPUT == 1)
		{
			int fd = open(my_struct->each_cmd[c_of_s].files[j].files,
					O_RDWR , 0777);
			if(fd == -1)
			{
				perror("error");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (my_struct->each_cmd[c_of_s].files[j].APPEND == 1)
		{
			int fd = open(my_struct->each_cmd[c_of_s].files[j].files,
					O_CREAT | O_RDWR | O_APPEND, 0777);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (my_struct->each_cmd[c_of_s].files[j].HERDOC == 1)
		{
			int file_origin = dup(STDIN_FILENO);
			int fd_by_pipe[2];
			char *beffer = 0;
			char *herdoc = ft_strdup("");
			pipe(fd_by_pipe);
			while (1)
			{
				beffer = readline("> ");
				if (!ft_strncmp(beffer,
						my_struct->each_cmd[c_of_s].files[j].files,
						ft_strlen(beffer)))
					break ;
				herdoc = ft_strjoin(herdoc, beffer);
				herdoc = ft_strjoin(herdoc, "\n");
			}
			ft_putstr_fd(herdoc, fd_by_pipe[1]);
			free(herdoc);
			close(fd_by_pipe[1]);
			dup2(fd_by_pipe[1], STDIN_FILENO);
			close(fd_by_pipe[0]);
			if (my_struct->each_cmd[c_of_s].files[j + 1].HERDOC == 1)
				dup2(file_origin, STDIN_FILENO);
			close(file_origin);
		}
		j++;
	}
}