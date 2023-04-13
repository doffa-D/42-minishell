/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:13:17 by nouakhro          #+#    #+#             */
/*   Updated: 2022/10/13 15:18:21 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*head;

	if (!lst || !del)
		return ;
	head = *lst;
	while (*lst)
	{
		head = head->next;
		ft_lstdelone(*lst, del);
		*lst = head;
	}
}
