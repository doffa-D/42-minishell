/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/05 20:29:34 by nouakhro         ###   ########.fr       */
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

void free_all_v2(int num,t_all *_struct)
{
	int i = 0;
	int j = 0;
	if(num == 1)
	{
		while(_struct->my_path[i])
		{
			free(_struct->my_path[i]);
			i++;
		}
		free(_struct->my_path);
	}
	i = 0;
	j = 0;
	while(_struct->each_cmd[i].files)
	{
		j = 0;
		while (_struct->each_cmd[i].files[j].files)
		{
			free(_struct->each_cmd[i].files[j].files);
			j++;
		}
		free(_struct->each_cmd[i].files);
		i++;
	}
	i = 0;
	while(_struct->each_cmd[i].cmd)
	{
		j = 0;
		while (_struct->each_cmd[i].cmd[j])
		{
			free(_struct->each_cmd[i].cmd[j]);
			j++;
		}
		free(_struct->each_cmd[i].cmd);
		i++;
	}
	free(_struct->each_cmd);
}


int cd_commade(t_all *_struct, int c_of_s)
{
	int pid = 0;
	if(_struct->each_cmd[c_of_s].cmd[1] && access(_struct->each_cmd[c_of_s].cmd[1], F_OK) == -1)
	{
		dup2(2, 1);
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		return 1;
	}
    if((ft_strlen(_struct->each_cmd[c_of_s].cmd[0]) == 2 && _struct->each_cmd[c_of_s].cmd[1] && (_struct->each_cmd[c_of_s].cmd[1][0] == '~' \
	|| _struct->each_cmd[c_of_s].cmd[1][1] == '/')))
    {
		if(_struct->each_cmd[c_of_s].cmd[1][0] == '~')
		{

        	chdir(my_getenv(_struct->list,"HOME", 0));

		}
		if(_struct->each_cmd[c_of_s].cmd[1] && _struct->each_cmd[c_of_s].cmd[1][1] == '/')
		{
            chdir(_struct->each_cmd[c_of_s].cmd[1]);
		}
    }
	if(ft_strlen(_struct->each_cmd[c_of_s].cmd[0]) == 2 && !_struct->each_cmd[c_of_s].cmd[1])
	{
        if(chdir(my_getenv(_struct->list,"HOME", 0)) == -1)
		{
			pid = fork();
			if(pid == 0)
			{
				dup2(2, 1);
				printf("minishell: %s: HOME not set\n", _struct->each_cmd[c_of_s].cmd[0]);
				exit(1);
			}
			wait(&pid);
			return 1;
		}
	}
    else
        chdir(_struct->each_cmd[c_of_s].cmd[1]);
	int x;
	int i;
	char *cmd = ft_strdup("PWD");
	x = 0;
	i = 0;
	t_list *old_list = _struct->list;
	while (_struct->list != NULL)
	{
		while (cmd[i])
		{
			if (((char *)_struct->list->content)[i]
				&& ((char *)_struct->list->content)[i] == cmd[i])
			{
				i++;
				if (((char *)_struct->list->content)[i] == '='
					|| ((char *)_struct->list->content)[i] == 0)
					x = 1;
			}
			else
				break ;
		}
		if (x == 1)
			break ;
		_struct->list = _struct->list->next;
	}
	char	wd[255];
	wd[255 - 1] = '\0';
	free(_struct->list->content);
	_struct->list->content = ft_strjoin(ft_strdup("PWD="),getcwd(wd, 255 - 1));
	free(cmd);
	_struct->list = old_list;
    return (0);
}



int if_builtins_in_parent(t_all *_struct, int c_of_s)
{
	if(_struct->each_cmd[c_of_s].cmd[0] && ft_strlen(_struct->each_cmd[c_of_s].cmd[0]) \
	 &&!ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "cd", ft_strlen(_struct->each_cmd[c_of_s].cmd[0])))
		return (1);
	if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
		return (1);
	else if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
		return (1);
	else if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
		return (1);
	else if (_struct->each_cmd[c_of_s].cmd && _struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "exit", ft_strlen("exit")))
		return (1);
	return (0);
}

int if_builtins_in_chiled(t_all *_struct, int c_of_s)
{
	if(_struct->each_cmd[c_of_s].cmd[0] && ft_strlen(_struct->each_cmd[c_of_s].cmd[0]) \
	 &&!ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "cd", ft_strlen(_struct->each_cmd[c_of_s].cmd[0])))
		return (1);
	if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
		return (1);
	if (_struct->each_cmd[0].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "echo", ft_strlen("echo")+1))
		return (1);
	if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "pwd", ft_strlen("pwd")+1))
		return (1);
	else if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
		return (1);
	else if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
		return (1);
	else if (_struct->each_cmd[c_of_s].cmd && _struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "exit", ft_strlen("exit")))
		return (1);
	return (0);
}

int builtins_in_parent(t_all *_struct, int c_of_s)
{
	int i = 0;
	if(_struct->each_cmd[c_of_s].cmd[0] && ft_strlen(_struct->each_cmd[c_of_s].cmd[0]) \
	 &&!ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "cd", ft_strlen(_struct->each_cmd[c_of_s].cmd[0])))
	{
		if(cd_commade(_struct, c_of_s))
			return (-1);
		return (1);
	}
	if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
	{
		_struct->check = 0;
		export_command(_struct,c_of_s);

		if(_struct->check == 1)
			return (-1);
		return (1);
	}
	else if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
	{
		env_command(_struct->list);
		return (1);
	}
	else if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
	{
		unset_command(_struct,c_of_s);
		return (1);
	}
	else if (_struct->each_cmd[c_of_s].cmd && _struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "exit", ft_strlen("exit")))
	{
		
		if(_struct->each_cmd[c_of_s].cmd && _struct->each_cmd[c_of_s].cmd[1])
		{
			while (_struct->each_cmd[c_of_s].cmd[1][i])
			{
				if(ft_isalpha(_struct->each_cmd[c_of_s].cmd[1][i]))
				{
					dup2(2, 1);
					printf("minishell: exit: %s: numeric argument required\n", _struct->each_cmd[c_of_s].cmd[1]);
					exit(255);
				}
				i++;
			}
			if(!_struct->each_cmd[c_of_s].cmd[2])
				exit(ft_atoi(_struct->each_cmd[c_of_s].cmd[1]));
		}
		if(_struct->each_cmd[c_of_s].cmd && _struct->each_cmd[c_of_s].cmd[1] && _struct->each_cmd[c_of_s].cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return -1;
		}
		exit(_struct->exit_status);
	}
	return (0);
}

int builtins(t_all *_struct, int c_of_s)
{
	int i = 0;
	if(_struct->each_cmd[c_of_s].cmd[0] && ft_strlen(_struct->each_cmd[c_of_s].cmd[0]) \
	 &&!ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "cd", ft_strlen(_struct->each_cmd[c_of_s].cmd[0])))
	{
		if(cd_commade(_struct, c_of_s))
			exit(1);
		exit(0);
	}
	if (_struct->each_cmd[0].cmd[0] && \
	!ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "echo", ft_strlen("echo")+1))
	{
		echo_command(_struct,c_of_s);
		exit(0);
	}
	if (_struct->each_cmd[c_of_s].cmd[0] && \
	!ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "pwd", ft_strlen("pwd")+1))
	{
		pwd_command();
		exit(0);
	}
	if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
	{
		_struct->check = 0;
		export_command(_struct,c_of_s);

		if(_struct->check == 1)
			exit(1);
		exit(0);

	}
	else if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
	{
		env_command(_struct->list);
		exit(0);
	}
	else if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
	{
		unset_command(_struct,c_of_s);
		exit(0);
	}
	else if (_struct->each_cmd[c_of_s].cmd && _struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "exit", ft_strlen("exit")))
	{
		
		if(_struct->each_cmd[c_of_s].cmd && _struct->each_cmd[c_of_s].cmd[1])
		{
			while (_struct->each_cmd[c_of_s].cmd[1][i])
			{
				if(ft_isalpha(_struct->each_cmd[c_of_s].cmd[1][i]))
				{
					dup2(2, 1);
					printf("minishell: exit: %s: numeric argument required\n", _struct->each_cmd[c_of_s].cmd[1]);
					exit(255);
				}
				i++;
			}
			if(!_struct->each_cmd[c_of_s].cmd[2])
				exit(ft_atoi(_struct->each_cmd[c_of_s].cmd[1]));
		}
		if(_struct->each_cmd[c_of_s].cmd && _struct->each_cmd[c_of_s].cmd[1] && _struct->each_cmd[c_of_s].cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			exit(1);
		}
		exit(_struct->exit_status);
	}

	return (0);
}
int	somting_in_readline(t_all *_struct)
{
	int		i;
	int		j;
	int		c_of_s = 0;
	int		checker;
	char	splite_char;
	i = 0;
	j = 0;
	_struct->tmp_cmd = 0;
	_struct->tmp_cmd = ft_strtrim(_struct->cmd, " ");
	if(!*_struct->tmp_cmd)
		return _struct->exit_status;
	_struct->the_commande = 0;
	while (_struct->tmp_cmd[i])
	{
		splite_char = ' ';
		checker = 0;
		while (_struct->tmp_cmd[i] && _struct->tmp_cmd[i] != splite_char)
		{
			if (_struct->tmp_cmd[i] == 34 && !checker)
			{
				splite_char = 34;
				checker = 1;
			}
			if (_struct->tmp_cmd[i] == 39 && !checker)
			{
				splite_char = 39;
				checker = 1;
			}
			i++;
		}
		if (splite_char != ' ' && _struct->tmp_cmd[i])
			i++;
		if (_struct->tmp_cmd[i] == ' ')
		{
			if (!_struct->the_commande)
				_struct->the_commande = ft_calloc(1, 1);
			_struct->tmp_cmd[i] = 3;
			i++;
			_struct->the_commande = ft_strjoin_v2(_struct->the_commande,
					ft_substr(_struct->tmp_cmd, j, i - j));
			j = i;
		}
		if (!_struct->tmp_cmd[i])
		{
			if (!_struct->the_commande)
				_struct->the_commande = ft_calloc(1, 1);
			_struct->the_commande = ft_strjoin_v2(_struct->the_commande,
					ft_substr(_struct->tmp_cmd, j, i - j));
			break ;
		}
	}
	i = 0;
	_struct->fix_cmd = ft_split(_struct->the_commande, 3);
	free(_struct->the_commande);
	free(_struct->tmp_cmd);
	add_history(_struct->cmd);
	_struct->the_commande = 0;
	_struct->tmp_cmd = 0;
	i = fix_arg(_struct);
	if(i == 258)
		return 258;
	if(i == 2)
		return 2;
	if(i == 1)
		return 1;
	c_of_s = 0;
	if(_struct->number_of_pipes == 1 && if_builtins_in_parent(_struct, c_of_s))
	{
		if(_struct->each_cmd[c_of_s].files)
		{
			int output_buckup = dup(STDOUT_FILENO);
			int input_buckup = dup(STDIN_FILENO);
			c_of_s = check_rediractions_in_parent(_struct, c_of_s);
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
			c_of_s = builtins_in_parent(_struct, c_of_s);
			dup2(output_buckup, STDOUT_FILENO);
			dup2(input_buckup, STDIN_FILENO);
			close(output_buckup);
			close(input_buckup);
		}
		else
			c_of_s = builtins_in_parent(_struct, c_of_s);
		if(c_of_s == 1)
		{
			free_all_v2(0 ,_struct);
			return 0;
		}
		if(c_of_s == -1)
		{
			free_all_v2(0, _struct);
			return 1;
		}
	}
	char *str = my_getenv(_struct->list, "PATH", 0);
	_struct->my_path = ft_split(str, ':');
	free(str);
	int *pid = malloc(_struct->number_of_pipes * sizeof(int));
	c_of_s = 0;
	while (c_of_s < _struct->number_of_pipes - 1)
	{
		pipe(_struct->each_cmd[c_of_s].fd);
		c_of_s++;
	}
	c_of_s = 0;
	while(_struct->number_of_pipes > 0)
	{
		i = fork();
		if (i == -1)
		{
			perror("fork");
			exit(1);
		}
		if (i == 0)
		{
			if(!_struct->my_path[0] && !if_builtins_in_chiled(_struct, c_of_s))
			{
				dup2(2, 1);
				printf("minishell: %s: No such file or directory\n", _struct->each_cmd[c_of_s].cmd[0]);
				exit(127);
			}
			if(c_of_s > 0)
			{
				close(_struct->each_cmd[c_of_s - 1].fd[1]);
				dup2(_struct->each_cmd[c_of_s - 1].fd[0], STDIN_FILENO);
				close(_struct->each_cmd[c_of_s - 1].fd[0]);
			}
			if(_struct->number_of_pipes > 1)
			{
				close(_struct->each_cmd[c_of_s].fd[0]);
				dup2(_struct->each_cmd[c_of_s].fd[1], STDOUT_FILENO);
				close(_struct->each_cmd[c_of_s].fd[1]);
			}
			if(_struct->each_cmd[c_of_s].files)
				check_rediractions(_struct, c_of_s);
			j = builtins(_struct, c_of_s);
			j = 0;
			if (_struct->each_cmd[c_of_s].cmd[0] && \
			!ft_strchr(_struct->each_cmd[c_of_s].cmd[0], '/') && !get_the_path(_struct, c_of_s))
			{
				i = 0;
				while (_struct->my_path && _struct->my_path[i])
				{
					if (access(_struct->my_path[i], F_OK) == 0)
					{
						j = 1;
						break ;
					}
					i++;
				}
			}
			else
			{
				if (_struct->each_cmd[c_of_s].cmd[0] && access(_struct->each_cmd[c_of_s].cmd[0], F_OK) == 0)
					j = 1;
			}
			if (j != 1)
			{
				if (_struct->each_cmd[c_of_s].cmd[0]
					&& (!ft_strchr(_struct->each_cmd[c_of_s].cmd[0], '/')))
				{
					dup2(2, 1);
					printf("minishell: %s: command not found\n", _struct->each_cmd[c_of_s].cmd[0]);
					exit(127);
				}
				else if (_struct->each_cmd[c_of_s].cmd[0] && ft_strchr(_struct->each_cmd[c_of_s].cmd[0], '/'))
				{
					if (!chdir(_struct->each_cmd[c_of_s].cmd[0]))
					{
						dup2(2, 1);
						printf("minishell: %s: Is a directory\n", _struct->each_cmd[c_of_s].cmd[0]);
						exit(126);
					}
					else
					{
						dup2(2, 1);
						printf("minishell: %s: No such file or directory\n", _struct->each_cmd[c_of_s].cmd[0]);
						exit(127);
					}
				}
			}
			else
				exicut_commande(_struct, i, c_of_s, 0);
		}
		else
			pid[c_of_s] = i;
		if(_struct->number_of_pipes > 1)
			close(_struct->each_cmd[c_of_s].fd[1]);
		_struct->number_of_pipes--;
		c_of_s++;
	}
	i = 0;
	while (i < c_of_s - 1)
	{
		close(_struct->each_cmd[i].fd[1]);
		close(_struct->each_cmd[i].fd[0]);
		i++;
	}
	i = 0;
	while(i < c_of_s)
	{
		waitpid(pid[i], &_struct->exit_status, 0);
		_struct->exit_status = _struct->exit_status >> 8;
		i++;
	}
	free(pid);
	free_all_v2(1, _struct);
	return (_struct->exit_status);
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
    t_all _struct;
    _struct.list = NULL;
    fill_linked_list(env, &_struct.list);
	_struct.exit_status = 0;
    int i = 0;
    while (1)
    {
		_struct.the_commande = 0;
        _struct.cmd = readline("escanour > ");
        if(!_struct.cmd)
            exit(_struct.exit_status);
        if(ft_strlen(_struct.cmd) != 0)
            _struct.exit_status = somting_in_readline(&_struct);
		free(_struct.cmd);
        i++;
    }
}