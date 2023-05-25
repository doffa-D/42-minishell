/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_command_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:31:05 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/14 01:39:28 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	mini_check_export(char *src)
{
	int		i;
	char	*variable;

	i = 0;
	while (src && src[i] && src[i] != '=')
		i++;
	variable = ft_substr(src, 0, i);
	if (!ft_isalpha(variable[0]) && variable[0] != '_')
	{
		free(variable);
		return (1);
	}
	i = 1;
	while (variable[i])
	{
		if (!ft_isalnum(variable[i]) && variable[i] != '_')
		{
			free(variable);
			return (1);
		}
		i++;
	}
	free(variable);
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
	free_excution_part_after_error(new_node);
	ft_lstadd_back(list, new_node);
}

void	add_string(t_list *list)
{
	int		x;
	int		i;
	char	*backup;
	char	*old;

	i = 0;
	while (list != NULL)
	{
		i = 0;
		old = ft_calloc(sizeof(char), ft_strlen(list->content) + 1);
		free_excution_part_after_error(old);
		x = mini_search(list->content, '=');
		while (i <= x)
		{
			old[i] = ((char *)list->content)[i];
			i++;
		}
		backup = ft_strjoin_v2(old, ft_strdup(&((char *)list->content)[x + 1]));
		free_excution_part_after_error(backup);
		free(list->content);
		list->content = ft_strdup(backup);
		free_excution_part_after_error(list->content);
		free(backup);
		list = list->next;
	}
}
