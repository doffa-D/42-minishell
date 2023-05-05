/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:19:24 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/05 18:09:21 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char **new_env(t_list *list)
{
	t_list *ptr = list;
	int i;
	i = 0;
	while(list != NULL)
	{
		list = list->next;
		i++;
	}
	char **dst = malloc(sizeof(char*) * (i + 1));
	i = 0;
	list = ptr;
	while(list != NULL)
	{
		dst[i] = list->content;
		list = list->next;
		i++;
	}
	list = ptr;
	dst[i] = 0;
	return dst;
}
void	exicut_commande(t_all *my_struct, int i, int c_of_s, int *pipe_n)
{
	(void)pipe_n;
	if(my_struct->each_cmd[c_of_s].cmd[0] && ft_strchr(my_struct->each_cmd[c_of_s].cmd[0], '/'))
		execve(my_struct->each_cmd[c_of_s].cmd[0], my_struct->each_cmd[c_of_s].cmd, new_env(my_struct->list));
	execve(my_struct->my_path[i], my_struct->each_cmd[c_of_s].cmd, new_env(my_struct->list));
}