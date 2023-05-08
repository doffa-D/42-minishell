/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:19:24 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 11:29:47 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_env(t_list *list)
{
	t_list	*ptr;
	int		i;
	char	**dst;

	ptr = list;
	i = 0;
	while (list != NULL)
	{
		list = list->next;
		i++;
	}
	dst = malloc(sizeof(char*) * (i + 1));
	i = 0;
	list = ptr;
	while (list != NULL)
	{
		dst[i] = list->content;
		list = list->next;
		i++;
	}
	list = ptr;
	dst[i] = 0;
	return (dst);
}

// void	exicut_commande(int i, int c_of_s, int *pipe_n)
// {
// 	(void)pipe_n;
// 	if (g_struct.each_cmd[c_of_s].cmd[0]
// 		&& ft_strchr(g_struct.each_cmd[c_of_s].cmd[0], '/'))
// 		execve(g_struct.each_cmd[c_of_s].cmd[0],
// 				g_struct.each_cmd[c_of_s].cmd, new_env(g_struct.list));
// 	execve(g_struct.my_path[i], g_struct.each_cmd[c_of_s].cmd,new_env(g_struct.list));
// }
void	exicut_commande(int i, int c_of_s, int *pipe_n)
{
	(void)pipe_n;
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& ft_strchr(g_struct.each_cmd[c_of_s].cmd[0], '/'))
		{
			if(execve(g_struct.each_cmd[c_of_s].cmd[0], g_struct.each_cmd[c_of_s].cmd, new_env(g_struct.list)) == -1)
			{
				dup2(2, 1);
				printf("minishell: %s: Is a directory\n", g_struct.each_cmd[c_of_s].cmd[0]);
				exit(127);
			}
		}
	if(execve(g_struct.my_path[i], g_struct.each_cmd[c_of_s].cmd, new_env(g_struct.list)) == -1)
	{
		dup2(2, 1);
		printf("minishell: %s: command not found\n", g_struct.each_cmd[c_of_s].cmd[0]);
		exit(127);
	}
}