/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_creat_linked_list.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:23:03 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 13:27:28 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"

void	fill_linked_list(char **dst, t_list **list)
{
	int		i;
	t_list	*new_node;

	i = 0;
	while (dst[i])
	{
		new_node = ft_lstnew(ft_strdup(dst[i]));
		ft_lstadd_back(list, new_node);
		i++;
	}
}
