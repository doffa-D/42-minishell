/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 13:00:47 by nouakhro         ###   ########.fr       */
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

void	free_commande_whit_out_path(int i, int j)
{
	i = 0;
	j = 0;
	while (g_struct.each_cmd[i].files)
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
	while (g_struct.each_cmd[i].cmd)
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

void	free_all_v2(int num)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (num == 1)
	{
		while (g_struct.my_path[i])
		{
			free(g_struct.my_path[i]);
			i++;
		}
		free(g_struct.my_path);
	}
	free_commande_whit_out_path(i, j);
}

int	if_builtins_in_parent(int c_of_s)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd",
			ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export",
			ft_strlen("export") + 1))
		return (1);
	else if (g_struct.each_cmd[c_of_s].cmd[0]
			&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env",
				ft_strlen("env") + 1))
		return (1);
	else if (g_struct.each_cmd[c_of_s].cmd[0]
			&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset",
				ft_strlen("unset") + 1))
		return (1);
	else if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0]
			&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit",
				ft_strlen("exit")))
		return (1);
	return (0);
}

int	_is_builtins(int c_of_s)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd",
			ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export",
			ft_strlen("export") + 1))
		return (1);
	if (g_struct.each_cmd[0].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "echo",
			ft_strlen("echo") + 1))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "pwd", ft_strlen("pwd")
			+ 1))
		return (1);
	return (0);
}

int	if_builtins_in_chiled(int c_of_s)
{
	if (_is_builtins(c_of_s))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")
			+ 1))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset",
			ft_strlen("unset") + 1))
		return (1);
	if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit",
			ft_strlen("exit")))
		return (1);
	return (0);
}

int	some_builtins_in_parent(int c_of_s)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd",
			ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
	{
		if (cd_commade(c_of_s))
			return (-1);
		return (1);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export",
			ft_strlen("export") + 1))
	{
		g_struct.check = 0;
		export_command(c_of_s);
		if (g_struct.check == 1)
			return (-1);
		return (1);
	}
	return (0);
}

int	builtins_in_parent(int c_of_s)
{
	int	i;

	i = some_builtins_in_parent(c_of_s);
	if (i != 0)
		return (i);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")
			+ 1))
	{
		env_command(g_struct.list);
		return (1);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset",
			ft_strlen("unset") + 1))
	{
		if (unset_command(c_of_s))
			return (-1);
		return (1);
	}
	if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit",
			ft_strlen("exit")))
		_exit(c_of_s);
	return (0);
}

void	some_builtins(int c_of_s)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd",
			ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
	{
		if (cd_commade(c_of_s))
			exit(1);
		exit(0);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0] \
	&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "echo", ft_strlen("echo")
		+ 1))
	{
		echo_command(c_of_s);
		exit(0);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0] \
	&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "pwd", ft_strlen("pwd")
			+ 1))
	{
		pwd_command();
		exit(0);
	}
}

void	another_builtins(int c_of_s)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export",
			ft_strlen("export") + 1))
	{
		g_struct.check = 0;
		export_command(c_of_s);
		if (g_struct.check == 1)
			exit(1);
		exit(0);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")
			+ 1))
	{
		env_command(g_struct.list);
		exit(0);
	}
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset",
			ft_strlen("unset") + 1))
	{
		unset_command(c_of_s);
		exit(0);
	}
}

int	builtins(int c_of_s)
{
	some_builtins(c_of_s);
	another_builtins(c_of_s);
	if (g_struct.each_cmd[c_of_s].cmd && g_struct.each_cmd[c_of_s].cmd[0]
		&& !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit",
			ft_strlen("exit")))
		_exit(c_of_s);
	return (0);
}

void	_exit(int c_of_s)
{
	int	i;

	i = 0;
	exit_error_not_numeric(c_of_s, i);
	if (g_struct.each_cmd[c_of_s].cmd[1] && g_struct.each_cmd[c_of_s].cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit(1);
	}
	exit(g_struct.exit_status);
}

void	exit_error_not_numeric(int c_of_s, int i)
{
	if (g_struct.each_cmd[c_of_s].cmd[1])
	{
		if (!ft_isdigit(g_struct.each_cmd[c_of_s].cmd[1][i])
			&& g_struct.each_cmd[c_of_s].cmd[1][i] != '-'
			&& g_struct.each_cmd[c_of_s].cmd[1][i] != '+')
		{
			dup2(2, 1);
			printf("minishell: exit: %s: numeric argument required\n",
				g_struct.each_cmd[c_of_s].cmd[1]);
			exit(255);
		}
		i++;
		while (g_struct.each_cmd[c_of_s].cmd[1][i])
		{
			if (!ft_isdigit(g_struct.each_cmd[c_of_s].cmd[1][i]))
			{
				dup2(2, 1);
				printf("minishell: exit: %s: numeric argument required\n",
					g_struct.each_cmd[c_of_s].cmd[1]);
				exit(255);
			}
			i++;
		}
		if (!g_struct.each_cmd[c_of_s].cmd[2])
			exit(ft_atoi(g_struct.each_cmd[c_of_s].cmd[1]));
	}
}

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
			g_struct.the_commande = ft_calloc(1, 1);
		g_struct.tmp_cmd[i] = 3;
		i++;
		g_struct.the_commande = ft_strjoin_v2(g_struct.the_commande, \
		ft_substr(g_struct.tmp_cmd, *j, i - *j));
		*j = i;
	}
	return (i);
}

int	each_argemnt(int i, int j)
{
	int		checker;
	char	splite_char;

	g_struct.tmp_cmd = 0;
	g_struct.tmp_cmd = ft_strtrim(g_struct.cmd, " ");
	if (!*g_struct.tmp_cmd)
		return (g_struct.exit_status);
	g_struct.the_commande = 0;
	while (g_struct.tmp_cmd[i])
	{
		splite_char = ' ';
		checker = 0;
		i = splite_argemnt(i, checker, &splite_char);
		i = represent_between_each_argemnt(splite_char, i, &j);
		if (!g_struct.tmp_cmd[i])
		{
			if (!g_struct.the_commande)
				g_struct.the_commande = ft_calloc(1, 1);
			g_struct.the_commande = ft_strjoin_v2(g_struct.the_commande, \
			ft_substr(g_struct.tmp_cmd, j, i - j));
			break ;
		}
	}
	return (1);
}

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

int	after_parccing(int c_of_s)
{
	int	i;

	i = 0;
	c_of_s = _parent_builtins(c_of_s);
	if (c_of_s != 2)
		return (c_of_s);
	_path_comanmde();
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

int	_parent_builtins(int c_of_s)
{
	if (g_struct.number_of_pipes == 1 && if_builtins_in_parent(c_of_s))
	{
		if (g_struct.each_cmd[c_of_s].files)
			return (rederaction_and_builtins(c_of_s));
		else
			c_of_s = builtins_in_parent(c_of_s);
		if (c_of_s == 1)
		{
			free_all_v2(0);
			return (0);
		}
		if (c_of_s == -1)
		{
			free_all_v2(0);
			return (1);
		}
	}
	return (2);
}

void	_path_comanmde(void)
{
	int		i;
	int		j;
	char	*path;
	char	*str;

	i = 0;
	j = 0;
	path = ft_strdup("");
	str = my_getenv(g_struct.list, "PATH", 0);
	while (str[i])
	{
		if (str[i] == ':' && (str[i + 1] != ':'))
		{
			path = ft_strjoin_v2(path, ft_substr(str, j, i - j));
			j = i;
			if (i == 0 || i == (int)ft_strlen(str) \
			|| (str[i - 1] && str[i - 1] == ':'))
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
}

int	exicut_bultins(int c_of_s, int output_buckup, int input_buckup)
{
	c_of_s = builtins_in_parent(c_of_s);
	if (c_of_s != 0)
		return (c_of_s);
	dup2(output_buckup, STDOUT_FILENO);
	dup2(input_buckup, STDIN_FILENO);
	close(output_buckup);
	close(input_buckup);
	return (0);
}

void	return_fils_to_default(int output_buckup, int input_buckup)
{
	dup2(output_buckup, STDOUT_FILENO);
	dup2(input_buckup, STDIN_FILENO);
	close(output_buckup);
	close(input_buckup);
}

int	rederaction_and_builtins(int c_of_s)
{
	int	output_buckup;
	int	input_buckup;

	output_buckup = dup(STDOUT_FILENO);
	input_buckup = dup(STDIN_FILENO);
	c_of_s = check_rediractions_in_parent(c_of_s);
	if (c_of_s == -1)
	{
		return_fils_to_default(output_buckup, input_buckup);
		return (0);
	}
	if (c_of_s == 1)
	{
		return_fils_to_default(output_buckup, input_buckup);
		return (1);
	}
	c_of_s = exicut_bultins(c_of_s, output_buckup, input_buckup);
	if (c_of_s != 0)
		return (c_of_s);
	return (0);
}

void	pipe_is_exist_or_its_not_builtins(int c_of_s, int i)
{
	int	*pid;

	c_of_s = 0;
	pid = malloc(g_struct.number_of_pipes * sizeof(int));
	while (g_struct.number_of_pipes > 0)
	{
		i = fork();
		if (i == -1)
		{
			perror("fork");
			exit(1);
		}
		if (i == 0)
			check_error_and_excute_comande(c_of_s);
		else
			pid[c_of_s] = i;
		if (g_struct.number_of_pipes > 1)
			close(g_struct.each_cmd[c_of_s].fd[1]);
		g_struct.number_of_pipes--;
		c_of_s++;
	}
	wait_and_close_all(c_of_s, pid);
	free(pid);
}

void	check_error_and_excute_comande(int c_of_s)
{
	int	j;
	int	i;

	path_doase_not_exist(c_of_s);
	handel_pipe_and_rederaction(c_of_s);
	j = builtins(c_of_s);
	j = 0;
	i = 0;
	if (g_struct.each_cmd[c_of_s].cmd[0] \
	&& !ft_strchr(g_struct.each_cmd[c_of_s].cmd[0], '/')
		&& !get_the_path(c_of_s))
		j = join_path_whit_commade(c_of_s, j, &i);
	else
		j = path_is_exist(c_of_s, j);
	if (j != 1)
		error_is_exist(c_of_s);
	else
		exicut_commande(i, c_of_s, 0);
}

void	path_doase_not_exist(int c_of_s)
{
	if (!g_struct.my_path[0] && !if_builtins_in_chiled(c_of_s))
	{
		dup2(2, 1);
		printf("minishell: %s: No such file or directory\n",
			g_struct.each_cmd[c_of_s].cmd[0]);
		exit(127);
	}
}

void	handel_pipe_and_rederaction(int c_of_s)
{
	if (c_of_s > 0)
	{
		close(g_struct.each_cmd[c_of_s - 1].fd[1]);
		dup2(g_struct.each_cmd[c_of_s - 1].fd[0], STDIN_FILENO);
		close(g_struct.each_cmd[c_of_s - 1].fd[0]);
	}
	if (g_struct.number_of_pipes > 1)
	{
		close(g_struct.each_cmd[c_of_s].fd[0]);
		dup2(g_struct.each_cmd[c_of_s].fd[1], STDOUT_FILENO);
		close(g_struct.each_cmd[c_of_s].fd[1]);
	}
	if (g_struct.each_cmd[c_of_s].files)
		check_rediractions(c_of_s);
}

int	path_is_exist(int c_of_s, int j)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& access(g_struct.each_cmd[c_of_s].cmd[0], F_OK) == 0)
	{
		if (access(g_struct.each_cmd[c_of_s].cmd[0], X_OK) == 0)
			j = 1;
		else
		{
			printf("minishell: %s: Permission denied\n",
				g_struct.each_cmd[c_of_s].cmd[0]);
			exit(126);
		}
	}
	return (j);
}

int	join_path_whit_commade(int c_of_s, int j, int *i)
{
	*i = 0;
	while (g_struct.my_path && g_struct.my_path[*i])
	{
		if (access(g_struct.my_path[*i], F_OK) == 0)
		{
			if (access(g_struct.my_path[*i], X_OK) == 0)
			{
				j = 1;
				break ;
			}
			else
			{
				printf("minishell: %s: Permission denied\n",
					g_struct.each_cmd[c_of_s].cmd[0]);
				exit(126);
			}
		}
		(*i)++;
	}
	return (j);
}

void	error_in_commande(int c_of_s)
{
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& (!ft_strchr(g_struct.each_cmd[c_of_s].cmd[0], '/')))
	{
		dup2(2, 1);
		printf("minishell: %s: command not found\n",
			g_struct.each_cmd[c_of_s].cmd[0]);
		exit(127);
	}
}

void	error_is_exist(int c_of_s)
{
	error_in_commande(c_of_s);
	if (g_struct.each_cmd[c_of_s].cmd[0]
		&& ft_strchr(g_struct.each_cmd[c_of_s].cmd[0], '/'))
	{
		if (!chdir(g_struct.each_cmd[c_of_s].cmd[0]))
		{
			dup2(2, 1);
			printf("minishell: %s: Is a directory\n",
				g_struct.each_cmd[c_of_s].cmd[0]);
			exit(126);
		}
		else
		{
			dup2(2, 1);
			printf("minishell: %s: No such file or directory\n",
				g_struct.each_cmd[c_of_s].cmd[0]);
			exit(127);
		}
	}
}

void	wait_and_close_all(int c_of_s, int *pid)
{
	int	i;

	i = 0;
	if(g_struct.fils_descreprot != 0)
		close(g_struct.fils_descreprot);
	while (i < c_of_s - 1)
	{
		close(g_struct.each_cmd[i].fd[1]);
		close(g_struct.each_cmd[i].fd[0]);
		i++;
	}
	i = 0;
	while (i < c_of_s)
	{
		waitpid(pid[i], &g_struct.exit_status, 0);
		if (WIFEXITED(g_struct.exit_status))
			g_struct.exit_status = WEXITSTATUS(g_struct.exit_status);
		else if (WIFSIGNALED(g_struct.exit_status))
			g_struct.exit_status = WTERMSIG(g_struct.exit_status) + 128;
		i++;
	}
}

void	fill_linked_list(char **dst, t_list **list)
{
	int		i;
	t_list	*new_node;

	i = 0;
	while (dst[i])
	{
		new_node = ft_lstnew(ft_strdup(dst[i]));
		ft_lstadd_back(list, new_node);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;

	(void)argv;
	(void)argc;
	g_struct.list = NULL;
	fill_linked_list(env, &g_struct.list);
	g_struct.exit_status = 0;
	// signal(SIGINT, &handler);
	// signal(SIGQUIT, &handler);
	i = 0;
	while (1)
	{
		g_struct.the_commande = 0;
		g_struct.cmd = readline("escanour > ");
		if (!g_struct.cmd)
			exit(g_struct.exit_status);
		if (ft_strlen(g_struct.cmd) != 0)
			g_struct.exit_status = somting_in_readline();
		free(g_struct.cmd);
		i++;
	}
}
