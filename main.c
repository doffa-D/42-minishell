/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/18 03:30:09 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../get_next_line/get_next_line.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		return ;
}
// int cd_commade(t_all my_struct)
// {
//     // printf("fdfvfd\n");
//     if(my_struct.my_command[0] && ft_strlen(my_struct.cmd)
		// && !ft_strncmp(my_struct.my_command[0], "cd",
		// 	ft_strlen(my_struct.my_command[0])))
//     {
//         // printf("test[%s]\n", my_struct.my_command[1]);
//         if((ft_strlen(my_struct.cmd) == 2
			// || my_struct.my_command[1][0] == '~'))
//         {
//             chdir(getenv("HOME"));
//             if(my_struct.my_command[1] && my_struct.my_command[1][1] == '/'
		// && my_struct.my_command[1][2])
//                 chdir(my_struct.my_command[1] + 2);
//         }
//         // else if(ft_strlen(my_struct.cmd) == 2
		// || (my_struct.my_command[1][0] == '-' &&  my_struct.my_command[1][1]))
//         //     chdir(my_struct.my_all_path[loop
		// - (ft_atoi(&my_struct.my_command[1][1])) + 1]);
//         // else if(ft_strlen(my_struct.cmd) == 2
		// || my_struct.my_command[1][0] == '-')
//         //     chdir(my_struct.my_all_path[loop]);
//         else
//             chdir(my_struct.my_command[1]);
//         my_struct.i = 0;
//     }
//     return (0);
// }
int	somting_in_readline(t_all *my_struct)
{
	int		i;
	int		j;
	int		checker;
	char	splite_char;
	int		c_of_s = 0;

	i = 0;
	j = 0;
	checker = 0;
	my_struct->tmp_cmd = 0;
	my_struct->tmp_cmd = ft_strdup(my_struct->cmd);
	my_struct->the_commande = 0;
	while (my_struct->tmp_cmd[i])
	{
		splite_char = ' ';
		checker = 0;
		while (my_struct->tmp_cmd[i] && my_struct->tmp_cmd[i] != splite_char)
		{
			if (my_struct->tmp_cmd[i] == 34 && !checker)
			{
				splite_char = 34;
				checker = 1;
			}
			if (my_struct->tmp_cmd[i] == 39 && !checker)
			{
				splite_char = 39;
				checker = 1;
			}
			i++;
		}
		if (splite_char != ' ')
			i++;
		if (my_struct->tmp_cmd[i] == ' ')
		{
			if (!my_struct->the_commande)
				my_struct->the_commande = ft_calloc(1, 1);
			my_struct->tmp_cmd[i] = 3;
			i++;
			my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,
					ft_substr(my_struct->tmp_cmd, j, i - j));
			j = i;
		}
		if (!my_struct->tmp_cmd[i])
		{
			if (!my_struct->the_commande)
				my_struct->the_commande = ft_calloc(1, 1);
			my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,
					ft_substr(my_struct->tmp_cmd, j, i - j));
			break ;
		}
	}
	my_struct->fix_cmd = ft_split(my_struct->the_commande, 3);
	free(my_struct->the_commande);
	free(my_struct->tmp_cmd);
	add_history(my_struct->cmd);
	my_struct->the_commande = 0;
	my_struct->tmp_cmd = 0;
	i = 0;
	fix_arg(my_struct);
	my_struct->my_path = ft_split(getenv("PATH"), ':');
	// while (my_struct->my_path[i])
	// {
	//     printf("%s\n", my_struct->my_path[i]);
	//     free(my_struct->my_path[i]);
	//     i++;
	// }
	// free(my_struct->my_path);
	// i = 0;
	// while (my_struct->each_cmd->cmd[i])
	// {
	//     printf("%s\n", my_struct->each_cmd->cmd[i]);
	//     free(my_struct->each_cmd->cmd[i]);
	//     i++;
	// }
	// free(my_struct->each_cmd->cmd);
	// free(my_struct->each_cmd);
	// check_leaks();
	// exit(0);
	int pipe_n[2];
	pipe(pipe_n);
	c_of_s = 0;
	while(my_struct->number_of_pipes > 0)
	{
		int k = 0;
		i = fork();
		if (i == 0)
		{
			if(c_of_s > 0)
			{
				if(my_struct->number_of_pipes > 0)
				{
					dup2(pipe_n[0], STDIN_FILENO);
					close(pipe_n[0]);	
				}
			}
			if(my_struct->number_of_pipes > 1)
			{
				dup2(pipe_n[1], STDOUT_FILENO);
				close(pipe_n[1]);
			}
			j = 0;
			if (!get_the_path(my_struct, c_of_s))
			{
				i = 0;
				while (my_struct->my_path[i])
				{
					if (access(my_struct->my_path[i], F_OK) == 0)
					{
						j = 1;
						break ;
					}
					i++;
				}
			}
			if (j != 1)
			{
				if (my_struct->each_cmd[c_of_s].cmd[0]
					&& !ft_strchr(my_struct->each_cmd[c_of_s].cmd[0], '/'))
				{
					printf("%s: command not found\n",
							my_struct->each_cmd[c_of_s].cmd[0]);
					exit(127);
				}
				else if (ft_strchr(my_struct->each_cmd[c_of_s].cmd[0], '/'))
				{
					if (!chdir(my_struct->each_cmd[c_of_s].cmd[0]))
						printf("%s: is a directory\n",
								my_struct->each_cmd[c_of_s].cmd[0]);
					else
					{
						printf("%s: No such file or directory\n",
								my_struct->each_cmd[c_of_s].cmd[0]);
						printf("ppppppppppppppppp\n");
					}
				}
				exit(1);
			}
			else
				exicut_commande(my_struct, i, c_of_s);
		}
		waitpid(-1, &k, 0);
		c_of_s++;
		my_struct->number_of_pipes--;
	}
	// cd_commade(my_struct);
	// free_all(my_struct);
	return (0);
}
int	main(void)
{
	t_all my_struct;

	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	int i = 0;
	while (1)
	{
		my_struct.cmd = readline("escanour > ");
		my_struct.if_rediraction = 0;
		if (!my_struct.cmd)
			exit(0);
		if (ft_strlen(my_struct.cmd) != 0)
			somting_in_readline(&my_struct);
		i++;
	}
}