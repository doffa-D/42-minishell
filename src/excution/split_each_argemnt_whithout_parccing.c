/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_each_argemnt_whithout_parccing.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:33:51 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 20:23:14 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	splite_argemnt(int i, int checker, char *splite_char)
{
	while (g_struct.tmp_cmd[i] && g_struct.tmp_cmd[i] != *splite_char)
	{
		if (g_struct.tmp_cmd[i] == 34 && !checker)
		{
			*splite_char = 34;
			checker = 1;
		}
		if (g_struct.tmp_cmd[i] == 39 && !checker)
		{
			*splite_char = 39;
			checker = 1;
		}
		i++;
	}
	return (i);
}

int	represent_between_each_argemnt(char splite_char, int i, int *j)
{
	if (splite_char != ' ' && g_struct.tmp_cmd[i])
		i++;
	if (g_struct.tmp_cmd[i] == ' ')
	{
		if (!g_struct.the_commande)
		{
			g_struct.the_commande = ft_calloc(1, 1);
			if (!g_struct.the_commande)
			{
				free_linked_list();
				exit(1);
			}
		}
		g_struct.tmp_cmd[i] = 3;
		i++;
		g_struct.the_commande = ft_strjoin_v2(g_struct.the_commande, \
		ft_substr(g_struct.tmp_cmd, *j, i - *j));
		if (!g_struct.the_commande)
		{
			free_linked_list();
			exit(1);
		}
		*j = i;
	}
	return (i);
}

void	if_not_string(int i, int j)
{
	if (!g_struct.the_commande)
	{
		g_struct.the_commande = ft_calloc(1, 1);
		if (!g_struct.the_commande)
		{
			free_linked_list();
			exit(1);
		}
	}
	g_struct.the_commande = ft_strjoin_v2(g_struct.the_commande, \
	ft_substr(g_struct.tmp_cmd, j, i - j));
	if (!g_struct.the_commande)
	{
		free_linked_list();
		exit(1);
	}
}

int	each_argemnt(int i, int j)
{
	int		checker;
	char	splite_char;

	g_struct.tmp_cmd = 0;
	g_struct.tmp_cmd = ft_strtrim(g_struct.cmd, " ");
	if (!*g_struct.tmp_cmd || !g_struct.tmp_cmd)
	{
		if (g_struct.tmp_cmd)
			free(g_struct.tmp_cmd);
		return (g_struct.exit_status);
	}
	g_struct.the_commande = 0;
	while (g_struct.tmp_cmd[i])
	{
		splite_char = ' ';
		checker = 0;
		i = splite_argemnt(i, checker, &splite_char);
		i = represent_between_each_argemnt(splite_char, i, &j);
		if (!g_struct.tmp_cmd[i])
		{
			if_not_string(i, j);
			break ;
		}
	}
	return (-1);
}
