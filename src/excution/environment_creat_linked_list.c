/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_creat_linked_list.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:23:03 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 19:22:29 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fill_linked_list(char **dst, t_list **list)
{
	int		i;
	t_list	*new_node;

	i = 0;
	while (dst[i])
	{
		new_node = ft_lstnew(ft_strdup(dst[i]));
		if (!new_node && i != 0)
			free_linked_list();
		ft_lstadd_back(list, new_node);
		i++;
	}
}
