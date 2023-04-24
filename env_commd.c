/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:03:41 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/04/23 23:50:01 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_command(t_list *list)
{
	while (list != NULL)
	{
		if (mini_search(list->content, 61) != 0)
			printf("%s\n", list->content);
		list = list->next;
	}
}
