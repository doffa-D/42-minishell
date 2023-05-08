/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_return_somthing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:44:05 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 23:22:23 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	somting_in_readline(void)
{
	int	i;
	int	j;
	int	c_of_s;

	c_of_s = 0;
	i = 0;
	j = 0;
	if (each_argemnt(i, j) == 0)
		return (g_struct.exit_status);
	i = 0;
	g_struct.fix_cmd = ft_split(g_struct.the_commande, 3);
	free(g_struct.the_commande);
	free(g_struct.tmp_cmd);
	add_history(g_struct.cmd);
	g_struct.the_commande = 0;
	g_struct.tmp_cmd = 0;
	i = fix_arg();
	if (i != 0)
		return (i);
	i = after_parccing(c_of_s);
	if (i != 2)
		return (i);
	return (g_struct.exit_status);
}
