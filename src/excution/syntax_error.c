/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:08:08 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 23:59:34 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	syntax_error(t_var *variables)
{
	int	i;

	i = fork();
	error_fork(i, 0);
	if (i == 0)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		// ft_putstr_fd("minishell: syntax error rederaction\n", 2);
		exit(1);
	}
	wait(&i);
	i = -1;
	while (g_struct.each_cmd[++i].files)
		free(g_struct.each_cmd[i].files);
	free(g_struct.each_cmd);
	free(g_struct.tmp_cmd);
	free(g_struct.the_commande);
	while (g_struct.splite_pipe[variables->index_i])
		free(g_struct.splite_pipe[variables->index_i++]);
	free(g_struct.splite_pipe);
}
