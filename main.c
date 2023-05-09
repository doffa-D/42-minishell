/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 12:00:46 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		// rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		return ;
}

int	after_parccing(int c_of_s)
{
	int	i;

	i = 0;
	c_of_s = _parent_builtins(c_of_s);
	if (c_of_s != 2)
		return (c_of_s);
	_path_comanmde(i);
	c_of_s = 0;
	while (c_of_s < g_struct.number_of_pipes - 1)
	{
		pipe(g_struct.each_cmd[c_of_s].fd);
		c_of_s++;
	}
	c_of_s = 0;
	pipe_is_exist_or_its_not_builtins(c_of_s, i);
	free_all_v2(1);
	return (2);
}

void	del(void *node)
{
	free(node);
}

void	free_linked_list(void)
{
	ft_lstclear(&g_struct.list, del);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	g_struct.list = NULL;
	fill_linked_list(env, &g_struct.list);
	g_struct.exit_status = 0;
	// signal(SIGINT, &handler);
	// signal(SIGQUIT, &handler);
	while (1)
	{
		g_struct.the_commande = 0;
		g_struct.cmd = readline("escanour > ");
		if (!g_struct.cmd)
		{
			free_linked_list();
			exit(g_struct.exit_status);
		}
		if (ft_strlen(g_struct.cmd) != 0)
			g_struct.exit_status = somting_in_readline();
		free(g_struct.cmd);
	}
}
