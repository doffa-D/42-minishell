/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/07 17:24:14 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// 	if (sig == SIGQUIT)
// 		return ;
// }

void free_all_v2(int num)
{
	int i = 0;
	int j = 0;
	if(num == 1)
	{
		while(g_struct.my_path[i])
		{
			free(g_struct.my_path[i]);
			i++;
		}
		free(g_struct.my_path);
	}
	i = 0;
	j = 0;
	while(g_struct.each_cmd[i].files)
	{
		j = 0;
		while (g_struct.each_cmd[i].files[j].files)
		{
			free(g_struct.each_cmd[i].files[j].files);
			j++;
		}
		free(g_struct.each_cmd[i].files);
		i++;
	}
	i = 0;
	while(g_struct.each_cmd[i].cmd)
	{
		j = 0;
		while (g_struct.each_cmd[i].cmd[j])
		{
			free(g_struct.each_cmd[i].cmd[j]);
			j++;
		}
		free(g_struct.each_cmd[i].cmd);
		i++;
	}
	free(g_struct.each_cmd);
}

int idont_have(t_list *list,char *cmd)
{
    int x;
    int i;
    x = 0;
    i = 0;
    t_list *old_list = list;
    
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
    list = old_list;
    return x;
}

t_list *i_have(t_list *list,char *cmd)
{
    int x;
    int i;
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
    return list;
}

t_list *searcher(t_list *list,char *old)
{
    int x;
    int i;
    
    x = 0;
    i = 0;
    t_list *old_list = list;
    if(idont_have(list,"OLDPWD=") == 0)
    {
        t_list  *new_node; 
        new_node = ft_lstnew(ft_strjoin(ft_strdup("OLDPWD="),old));
        ft_lstadd_back(&list, new_node);
    }
    t_list *new = i_have(list,"OLDPWD");
    free(new->content);
    new->content = ft_strjoin(ft_strdup("OLDPWD="),old);
    list = old_list;
    t_list *new_1 = i_have(list,"PWD");
    free(new_1->content);
    new_1->content = ft_strjoin(ft_strdup("PWD="),getcwd(NULL, 255));
    list = old_list;
    return list;
}

int cd_commade(int c_of_s)
{
	int pid = 0;
	char *str;
	char *old;
    old = getcwd(NULL, 255);
    if((ft_strlen(g_struct.each_cmd[c_of_s].cmd[0]) == 2 && g_struct.each_cmd[c_of_s].cmd[1] && (g_struct.each_cmd[c_of_s].cmd[1][0] == '~' \
	|| g_struct.each_cmd[c_of_s].cmd[1][1] == '/')))
    {
		if(g_struct.each_cmd[c_of_s].cmd[1][0] == '~')
		{
			str = ft_strjoin(my_getenv(g_struct.list,"HOME",0),&g_struct.each_cmd[c_of_s].cmd[1][1]);
			if(chdir(str) == -1)
			{
				free(str);
				dup2(2, 1);
				ft_putstr_fd("minishell: No such file or directory\n", 2);
				return 1;
			}
			free(str);
		}
		else if(g_struct.each_cmd[c_of_s].cmd[1] && g_struct.each_cmd[c_of_s].cmd[1][1] == '/')
		{
			if(g_struct.each_cmd[c_of_s].cmd[1] && chdir(g_struct.each_cmd[c_of_s].cmd[1]) == -1)
			{
				dup2(2, 1);
				ft_putstr_fd("minishell: No such file or directory\n", 2);
				return 1;
			}
		}
    }
	if(ft_strlen(g_struct.each_cmd[c_of_s].cmd[0]) == 2 && !g_struct.each_cmd[c_of_s].cmd[1])
	{
        if(chdir(my_getenv(g_struct.list,"HOME", 0)) == -1)
		{
			pid = fork();
			if(pid == 0)
			{
				dup2(2, 1);
				printf("minishell: %s: HOME not set\n", g_struct.each_cmd[c_of_s].cmd[0]);
				exit(1);
			}
			wait(&pid);
			return 1;
		}
	}
    else
	{
		if(g_struct.each_cmd[c_of_s].cmd[1] && chdir(g_struct.each_cmd[c_of_s].cmd[1]) == -1)
		{
			dup2(2, 1);
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			return 1;
		}
	}
	searcher(g_struct.list,old);
    return (0);
}



int if_builtins_in_parent(int c_of_s)
{
	if(g_struct.each_cmd[c_of_s].cmd[0] && ft_strlen(g_struct.each_cmd[c_of_s].cmd[0]) \
	 &&!ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd", ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
		return (1);
	else if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
		return (1);
	else if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
		return (1);
	else if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit", ft_strlen("exit")))
		return (1);
	return (0);
}

int if_builtins_in_chiled(int c_of_s)
{
	if(g_struct.each_cmd[c_of_s].cmd[0] && ft_strlen(g_struct.each_cmd[c_of_s].cmd[0]) \
	 &&!ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd", ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
		return (1);
	if (g_struct.each_cmd[0].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "echo", ft_strlen("echo")+1))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "pwd", ft_strlen("pwd")+1))
		return (1);
	else if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
		return (1);
	else if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
		return (1);
	else if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit", ft_strlen("exit")))
		return (1);
	return (0);
}

int builtins_in_parent(int c_of_s)
{
	int i = 0;
	if(g_struct.each_cmd[c_of_s].cmd[0] && ft_strlen(g_struct.each_cmd[c_of_s].cmd[0]) \
	 &&!ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd", ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
	{
		if(cd_commade(c_of_s))
			return (-1);
		return (1);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
	{
		g_struct.check = 0;
		export_command(c_of_s);

		if(g_struct.check == 1)
			return (-1);
		return (1);
	}
	else if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
	{
		env_command(g_struct.list);
		return (1);
	}
	else if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
	{
		unset_command(c_of_s);
		return (1);
	}
	else if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit", ft_strlen("exit")))
	{
		
		i = 0;
		if(g_struct.each_cmd[c_of_s].cmd[1])
		{
			if (!ft_isdigit(g_struct.each_cmd[c_of_s].cmd[1][i]) \
			&& g_struct.each_cmd[c_of_s].cmd[1][i] != '-' \
			&& g_struct.each_cmd[c_of_s].cmd[1][i] != '+')
			{
				dup2(2, 1);
				printf("minishell: exit: %s: numeric argument required\n", g_struct.each_cmd[c_of_s].cmd[1]);
				exit(255);
			}
			i++;
			while (g_struct.each_cmd[c_of_s].cmd[1][i])
			{
				if(!ft_isdigit(g_struct.each_cmd[c_of_s].cmd[1][i]))
				{
					dup2(2, 1);
					printf("minishell: exit: %s: numeric argument required\n", g_struct.each_cmd[c_of_s].cmd[1]);
					exit(255);
				}
				i++;
			}

			if(!g_struct.each_cmd[c_of_s].cmd[2])
				exit(ft_atoi(g_struct.each_cmd[c_of_s].cmd[1]));
		}
		if(g_struct.each_cmd[c_of_s].cmd[1] && g_struct.each_cmd[c_of_s].cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			exit(1);
		}
		exit(g_struct.exit_status);
	}
	return (0);
}

int builtins(int c_of_s)
{
	int i = 0;
	if(g_struct.each_cmd[c_of_s].cmd[0] && ft_strlen(g_struct.each_cmd[c_of_s].cmd[0]) \
	 &&!ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd", ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
	{
		if(cd_commade( c_of_s))
			exit(1);
		exit(0);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0] && \
	!ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "echo", ft_strlen("echo")+1))
	{
		echo_command(c_of_s);
		exit(0);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0] && \
	!ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "pwd", ft_strlen("pwd")+1))
	{
		pwd_command();
		exit(0);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
	{
		g_struct.check = 0;
		export_command(c_of_s);

		if(g_struct.check == 1)
			exit(1);
		exit(0);

	}
	else if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
	{
		env_command(g_struct.list);
		exit(0);
	}
	else if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
	{
		unset_command(c_of_s);
		exit(0);
	}
	else if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit", ft_strlen("exit")))
	{
		i = 0;
		if(g_struct.each_cmd[c_of_s].cmd[1])
		{
			if (!ft_isdigit(g_struct.each_cmd[c_of_s].cmd[1][i]) \
			&& g_struct.each_cmd[c_of_s].cmd[1][i] != '-' \
			&& g_struct.each_cmd[c_of_s].cmd[1][i] != '+')
			{
				dup2(2, 1);
				printf("minishell: exit: %s: numeric argument required\n", g_struct.each_cmd[c_of_s].cmd[1]);
				exit(255);
			}
			i++;
			while (g_struct.each_cmd[c_of_s].cmd[1][i])
			{
				if(!ft_isdigit(g_struct.each_cmd[c_of_s].cmd[1][i]))
				{
					dup2(2, 1);
					printf("minishell: exit: %s: numeric argument required\n", g_struct.each_cmd[c_of_s].cmd[1]);
					exit(255);
				}
				i++;
			}
			if(!g_struct.each_cmd[c_of_s].cmd[2])
				exit(ft_atoi(g_struct.each_cmd[c_of_s].cmd[1]));
		}
		if(g_struct.each_cmd[c_of_s].cmd[1] && g_struct.each_cmd[c_of_s].cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			exit(1);
		}
		exit(g_struct.exit_status);
	}

	return (0);
}
int	somting_in_readline()
{
	int		i;
	int		j;
	int		c_of_s = 0;
	int		checker;
	char	splite_char;
	i = 0;
	j = 0;
	g_struct.tmp_cmd = 0;
	g_struct.tmp_cmd = ft_strtrim(g_struct.cmd, " ");
	if(!*g_struct.tmp_cmd)
		return g_struct.exit_status;
	g_struct.the_commande = 0;
	while (g_struct.tmp_cmd[i])
	{
		splite_char = ' ';
		checker = 0;
		while (g_struct.tmp_cmd[i] && g_struct.tmp_cmd[i] != splite_char)
		{
			if (g_struct.tmp_cmd[i] == 34 && !checker)
			{
				splite_char = 34;
				checker = 1;
			}
			if (g_struct.tmp_cmd[i] == 39 && !checker)
			{
				splite_char = 39;
				checker = 1;
			}
			i++;
		}
		if (splite_char != ' ' && g_struct.tmp_cmd[i])
			i++;
		if (g_struct.tmp_cmd[i] == ' ')
		{
			if (!g_struct.the_commande)
				g_struct.the_commande = ft_calloc(1, 1);
			g_struct.tmp_cmd[i] = 3;
			i++;
			g_struct.the_commande = ft_strjoin_v2(g_struct.the_commande,
					ft_substr(g_struct.tmp_cmd, j, i - j));
			j = i;
		}
		if (!g_struct.tmp_cmd[i])
		{
			if (!g_struct.the_commande)
				g_struct.the_commande = ft_calloc(1, 1);
			g_struct.the_commande = ft_strjoin_v2(g_struct.the_commande,
					ft_substr(g_struct.tmp_cmd, j, i - j));
			break ;
		}
	}
	i = 0;
	g_struct.fix_cmd = ft_split(g_struct.the_commande, 3);
	free(g_struct.the_commande);
	free(g_struct.tmp_cmd);
	add_history(g_struct.cmd);
	g_struct.the_commande = 0;
	g_struct.tmp_cmd = 0;
	i = fix_arg();
	if(i == 258)
		return 258;
	if(i == 2)
		return 2;
	if(i == 1)
		return 1;
	c_of_s = 0;
	if(g_struct.number_of_pipes == 1 && if_builtins_in_parent(c_of_s))
	{
		if(g_struct.each_cmd[c_of_s].files)
		{
			int output_buckup = dup(STDOUT_FILENO);
			int input_buckup = dup(STDIN_FILENO);
			c_of_s = check_rediractions_in_parent(c_of_s);
			if(c_of_s == -1)
			{
				dup2(output_buckup, STDOUT_FILENO);
				dup2(input_buckup, STDIN_FILENO);
				close(output_buckup);
				close(input_buckup);
				return 0;
			}
			if(c_of_s == 1)
			{
				dup2(output_buckup, STDOUT_FILENO);
				dup2(input_buckup, STDIN_FILENO);
				close(output_buckup);
				close(input_buckup);
				return 1;
			}
			c_of_s = builtins_in_parent(c_of_s);
			dup2(output_buckup, STDOUT_FILENO);
			dup2(input_buckup, STDIN_FILENO);
			close(output_buckup);
			close(input_buckup);
		}
		else
			c_of_s = builtins_in_parent(c_of_s);
		if(c_of_s == 1)
		{
			free_all_v2(0);
			return 0;
		}
		if(c_of_s == -1)
		{
			free_all_v2(0);
			return 1;
		}
	}
	i = 0;
	j = 0;
	char *path = ft_strdup("");
	char *str = my_getenv(g_struct.list, "PATH", 0);
	while (str[i])
	{
		if(str[i] == ':')
		{
			path = ft_strjoin_v2(path, ft_substr(str, j + 1, i - j));
			j = i;
			if((str[i + 1] && str[i + 1] == ':') || i == 0 || i == (int)ft_strlen(str))
			{
				path = ft_strjoin(path, ".");
				i++;
			}
		}
		i++;
	}
	free(str);
	g_struct.my_path = ft_split(path, ':');
	free(path);
	int *pid = malloc(g_struct.number_of_pipes * sizeof(int));
	c_of_s = 0;
	while (c_of_s < g_struct.number_of_pipes - 1)
	{
		pipe(g_struct.each_cmd[c_of_s].fd);
		c_of_s++;
	}
	c_of_s = 0;
	while(g_struct.number_of_pipes > 0)
	{
		i = fork();
		if (i == -1)
		{
			perror("fork");
			exit(1);
		}
		if (i == 0)
		{
			if(!g_struct.my_path[0] && !if_builtins_in_chiled(c_of_s))
			{
				dup2(2, 1);
				printf("minishell: %s: No such file or directory\n", g_struct.each_cmd[c_of_s].cmd[0]);
				exit(127);
			}
			if(c_of_s > 0)
			{
				close(g_struct.each_cmd[c_of_s - 1].fd[1]);
				dup2(g_struct.each_cmd[c_of_s - 1].fd[0], STDIN_FILENO);
				close(g_struct.each_cmd[c_of_s - 1].fd[0]);
			}
			if(g_struct.number_of_pipes > 1)
			{
				close(g_struct.each_cmd[c_of_s].fd[0]);
				dup2(g_struct.each_cmd[c_of_s].fd[1], STDOUT_FILENO);
				close(g_struct.each_cmd[c_of_s].fd[1]);
			}
			if(g_struct.each_cmd[c_of_s].files)
				check_rediractions(c_of_s);
			j = builtins(c_of_s);
			j = 0;
			if (g_struct.each_cmd[c_of_s].cmd[0] && \
			!ft_strchr(g_struct.each_cmd[c_of_s].cmd[0], '/') && !get_the_path(c_of_s))
			{
				i = 0;
				while (g_struct.my_path && g_struct.my_path[i])
				{
					if (access(g_struct.my_path[i], F_OK) == 0)
					{
						if(access(g_struct.my_path[i], X_OK) == 0)
						{
							j = 1;
							break ;
						}
						else
						{
							printf("minishell: %s: Permission denied\n", g_struct.each_cmd[c_of_s].cmd[0]);
							exit(126);
						}
					}
					i++;
				}
			}
			else
			{
				if (g_struct.each_cmd[c_of_s].cmd[0] && access(g_struct.each_cmd[c_of_s].cmd[0], F_OK) == 0)
				{
					// printf("csdcds\n");
					if(access(g_struct.each_cmd[c_of_s].cmd[0], X_OK) == 0)
						j = 1;
					else
					{
						printf("minishell: %s: Permission denied\n", g_struct.each_cmd[c_of_s].cmd[0]);
						exit(126);
					}

				}
			}
			if (j != 1)
			{
				if (g_struct.each_cmd[c_of_s].cmd[0]
					&& (!ft_strchr(g_struct.each_cmd[c_of_s].cmd[0], '/')))
				{
					dup2(2, 1);
					printf("minishell: %s: command not found\n", g_struct.each_cmd[c_of_s].cmd[0]);
					exit(127);
				}
				else if (g_struct.each_cmd[c_of_s].cmd[0] && ft_strchr(g_struct.each_cmd[c_of_s].cmd[0], '/'))
				{
					if (!chdir(g_struct.each_cmd[c_of_s].cmd[0]))
					{
						dup2(2, 1);
						printf("minishell: %s: Is a directory\n", g_struct.each_cmd[c_of_s].cmd[0]);
						exit(126);
					}
					else
					{
						dup2(2, 1);
						printf("minishell: %s: No such file or directory\n", g_struct.each_cmd[c_of_s].cmd[0]);
						exit(127);
					}
				}
			}
			else
				exicut_commande(i, c_of_s, 0);
		}
		else
			pid[c_of_s] = i;
		if(g_struct.number_of_pipes > 1)
			close(g_struct.each_cmd[c_of_s].fd[1]);
		g_struct.number_of_pipes--;
		c_of_s++;
	}
	i = 0;
	while (i < c_of_s - 1)
	{
		close(g_struct.each_cmd[i].fd[1]);
		close(g_struct.each_cmd[i].fd[0]);
		i++;
	}
	i = 0;
	while(i < c_of_s)
	{
		waitpid(pid[i], &g_struct.exit_status, 0);
		g_struct.exit_status = g_struct.exit_status >> 8;
		i++;
	}
	free(pid);
	free_all_v2(1);
	return (g_struct.exit_status);
}
void    fill_linked_list(char **dst, t_list **list)
{
    int     i;

    i = 0;
    while (dst[i])
    {
        t_list  *new_node; 
        new_node = ft_lstnew(ft_strdup(dst[i]));
        ft_lstadd_back(list, new_node);
        i++;
    }
}

int main(int argc,char **argv,char **env)
{
    (void)argv;
    (void)argc;
    g_struct.list = NULL;
    fill_linked_list(env, &g_struct.list);
	g_struct.exit_status = 0;
    int i = 0;
    while (1)
    {
		g_struct.the_commande = 0;
        g_struct.cmd = readline("escanour > ");
        if(!g_struct.cmd)
            exit(g_struct.exit_status);
        if(ft_strlen(g_struct.cmd) != 0)
            g_struct.exit_status = somting_in_readline();
		free(g_struct.cmd);
        i++;
    }
}