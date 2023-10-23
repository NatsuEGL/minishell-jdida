/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:01:31 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/23 22:30:55 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*searching_path(char *command, t_env **envp)
{
	char	*path;
	char	**path_splied;

	path = NULL;
	if (ft_strchr(command, '/') == 0)
		return (command_slash(command, envp));
	else
	{
		path = check_env(ft_strdup("PATH"), envp);
		if (!path)
			return (NULL);
		path_splied = check_path_for_command(path, command);
		free(path);
		if (!path_splied)
		{
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": command not found\n", 2);
			free(command);
			(*envp)->es = 127;
			exit (127);
		}
		return (path_splied[0]);
	}
}

int	builting_check(char *command)
{
	if (!ft_strcmp(command, "env")
		|| !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "exit"))
		return (0);
	return (1);
}

void	simple_command(t_exec *exec_val, t_env **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (exec_val->infile != STDIN_FILENO)
		{
			if (exec_val->infile == -1)
				exit(1);
			dup2(exec_val->infile, STDIN_FILENO);
			close(exec_val->infile);
		}
		if (exec_val->outfile != STDOUT_FILENO)
		{
			dup2(exec_val->outfile, STDOUT_FILENO);
			close(exec_val->outfile);
		}
		exec_func(exec_val, envp);
	}
	waitpid(pid, &status, 0);
	(*envp)->es = exit_status(status);
	simple_cmd(&exec_val);
	return ;
}
