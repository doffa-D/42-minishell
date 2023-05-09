/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:03:41 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/09 13:27:00 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"

void	env_command(t_list *list)
{
	while (list != NULL)
	{
		if (mini_search(list->content, 61) != 0)
			printf("%s\n", list->content);
		list = list->next;
	}
}
