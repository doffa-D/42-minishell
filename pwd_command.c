/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:19:18 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/09 01:54:24 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_lstadd_back(&list, new_node);
	}
	new = i_have(list, "OLDPWD");
	free(new->content);
	new->content = ft_strjoin(ft_strdup("OLDPWD="), old);
	list = old_list;
	new_1 = i_have(list, "PWD");
	free(new_1->content);
	new_1->content = ft_strjoin_v2(ft_strdup("PWD="), getcwd(NULL, 255));
	list = old_list;
	return (list);
}

void	pwd_command(void)
{
	char	wd[255];

	wd[255 - 1] = '\0';
	if (getcwd(wd, 255 - 1) != NULL)
		printf("%s\n", wd);
}
