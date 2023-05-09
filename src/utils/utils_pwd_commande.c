/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pwd_commande.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:18:30 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 19:45:49 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	dont_have_utils(t_list *list, char *cmd, int i, int x)
{
	while (cmd[i])
	{
		if (((char *)list->content)[i]
			&& ((char *)list->content)[i] == cmd[i])
		{
			i++;
			if (((char *)list->content)[i] == '='
				|| ((char *)list->content)[i] == 0)
				x = 1;
		}
		else
			break ;
	}
	return (x);
}

int	idont_have(t_list *list, char *cmd)
{
	int		x;
	int		i;
	t_list	*old_list;

	x = 0;
	i = 0;
	old_list = list;
	while (list != NULL)
	{
		x = dont_have_utils(list, cmd, i, x);
		if (x == 1)
			break ;
		list = list->next;
	}
	list = old_list;
	return (x);
}

t_list	*i_have(t_list *list, char *cmd)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (list != NULL)
	{
		while (cmd[i])
		{
			if (((char *)list->content)[i]
				&& ((char *)list->content)[i] == cmd[i])
			{
				i++;
				if (((char *)list->content)[i] == '='
					|| ((char *)list->content)[i] == 0)
					x = 1;
			}
			else
				break ;
		}
		if (x == 1)
			break ;
		list = list->next;
	}
	return (list);
}

void	free_excution_part_after_error(void *malloc_error)
{
	int	i;

	i = 0;
	if (!malloc_error)
	{
		free_linked_list();
		free_all_v2(0);
		exit(1);
	}
}

t_list	*searcher(t_list *list, char *old)
{
	t_list	*old_list;
	t_list	*new_node;
	t_list	*new;
	t_list	*new_1;

	old_list = list;
	if (idont_have(list, "OLDPWD=") == 0)
	{
		new_node = ft_lstnew(ft_strjoin(ft_strdup("OLDPWD="), old));
		free_excution_part_after_error(new_node);
		ft_lstadd_back(&list, new_node);
	}
	new = i_have(list, "OLDPWD");
	free(new->content);
	new->content = ft_strjoin(ft_strdup("OLDPWD="), old);
	free_excution_part_after_error(new->content);
	list = old_list;
	new_1 = i_have(list, "PWD");
	free(new_1->content);
	new_1->content = ft_strjoin_v2(ft_strdup("PWD="), getcwd(NULL, 255));
	free_excution_part_after_error(new_1->content);
	list = old_list;
	return (list);
}
