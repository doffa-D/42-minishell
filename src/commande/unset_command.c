/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:05:18 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/14 03:39:38 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	delete_node(t_list *list, t_list *head, int x)
{
	t_list	*back;

	back = head;
	if (x == 1)
	{
		while (back)
		{
			if (back->next->content == list->content)
				break ;
			back = back->next;
		}
		back->next = list->next;
		ft_lstdelone(list, del);
	}
}

int	first_varible(char *str, char *cmd, t_list *list)
{
	char	**dst;
	int		i;

	i = -1;
	dst = ft_split(str, '=');
	if (!ft_strncmp(cmd, dst[0], ft_strlen(dst[0]) + 1))
	{
		free(str);
		while (dst[++i])
			free(dst[i]);
		free(dst);
		*list = *list->next;
		return (1);
	}
	i = -1;
	while (dst[++i])
		free(dst[i]);
	free(dst);
	return (0);
}

int	unset_utils(t_list *list, char *cmd)
{
	if (list && !list->next)
	{
		ft_lstdelone(list, del);
		list = NULL;
		return (1);
	}
	if (first_varible(list->content, cmd, list) == 1)
		return (0);
	return (0);
}

void	unset_utils_2(t_list *list, char *cmd, int *x, int i)
{
	i = 0;
	while (cmd[i])
	{
		if (((char *)list->content)[i]
			&& ((char *)list->content)[i] == cmd[i])
		{
			if (i++ && (((char *)list->content)[i] == '='
				|| ((char *)list->content)[i] == 0))
				*x = 1;
		}
		else
			break ;
	}
}
