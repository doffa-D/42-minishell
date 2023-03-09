/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:03:34 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/10/12 16:20:43 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;

	if (!del || !lst)
		return ;
	ptr = *lst;
	while (*lst)
	{
		ft_lstdelone(*lst, del);
		ptr = (*lst)->next;
		*lst = ptr;
	}
}
