/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_command_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:31:05 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/04/27 16:45:30 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_check_export(char *src,int x)
{
	int	i;

	i = 0;
	if ((src[i] >= '0' && src[i] <= '9') || (ft_strchr(src, '-') && !ft_strchr(src, '=')) || (ft_strchr(src, '|') && !ft_strchr(src, '=')))
		return (1);
	while (src[i])
	{
		if(x == 0 && (src[i] == 58 || src[i] == 47))
			return (1);
		if (src[i] == 33  || src[i] == 35  || src[i] == 37 || src[i] == 38|| src[i] == 60 || (src[i] >= 40 && src[i] <= 44) || src[i] == 64 || (src[i] >= 91 && src[i] <= 94) || src[i] == 123 || src[i] == 125)
			return (1);
		i++;
	}
	return (0);
}

int	duplicate_check_export(t_list *list, char *dst)
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		if (!ft_strncmp(list->content, dst, ft_strlen(dst) + 1))
			return (i);
		list = list->next;
		i++;
	}
	return (0);
}

int	mini_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			return (i);
		}
		i++;
	}
	return (0);
}

void	add_node_back(char *str, t_list **list)
{
	t_list	*new_node;

	new_node = ft_lstnew(ft_strdup(str));
	ft_lstadd_back(list, new_node);
}

void	string_dakche(t_list *list)
{
	int		x;
	int		i;
	char	*backup;
	char	*old;

	i = 0;
	while (list != NULL)
	{
		i = 0;
		old = calloc(sizeof(char), ft_strlen(list->content) + 1);
		x = mini_search(list->content, '=');
		while (i <= x)
		{
			old[i] = ((char *)list->content)[i];
			i++;
		}
		backup = ft_strjoin_v2(old, ft_strdup(&((char *)list->content)[x + 1]));
		free(list->content);
		list->content = ft_strdup(backup);
		free(backup);
		list = list->next;
	}
}
