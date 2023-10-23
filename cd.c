/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:41:03 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/23 13:49:44 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_command(char **command, t_env **env)
{
	int		i;
	char	**p;

	p = NULL;
	i = 0;
	(*env)->flagcd = 0;
	if (!command[1])
		cd_home(env);
	else if (!ft_strcmp(check_env_cd("PWD", env), command[1]))
		return ;
	else if (command[1] && !ft_strcmp(command[1], "/"))
		cd_slash(env);
	else
	{
		p = ft_split(command[1], '/');
		if (check_split(p) == 0)
			(*env)->flagcd = access_confirm(p, env);
		else
			(*env)->flagcd = access_confirm1(p, env, -1);
		if (cd_command_norm((*env)->flagcd, p) == -1)
			return ;
		p = ft_split(command[1], '/');
		cd_loop(p, env);
		free_split(p);
	}
}

void	cd_home(t_env **env)
{
	char	*home;
	t_env	*tmp;
	char	*path;
	size_t	size;

	home = check_env(ft_strdup("HOME"), env);
	tmp = (*env);
	path = NULL;
	size = 0;
	if (cd_error(home, 1, env) == -1)
		return (free(home));
	free(home);
	cd_next_env(tmp, env);
	tmp = *env;
	home = getcwd(path, size);
	if (home != NULL)
		cdhome_norm(tmp, &home, env);
}

void	cd_back(t_env **env)
{
	t_env	*envp;
	char	*path;
	char	*opwd;
	char	*gwc;
	size_t	size;

	envp = (*env);
	path = NULL;
	opwd = ft_path(env);
	if (opwd[0] == '\0')
		opwd = cd_back_free(opwd);
	size = 0;
	cd_error(opwd, 0, env);
	cd_next_env(envp, env);
	envp = *env;
	gwc = getcwd(path, size);
	if (gwc != NULL)
		cdback_norm(envp, &opwd);
	free(gwc);
}

void	cd_next(char *command, t_env **env)
{
	t_env	*envp;
	char	*path;
	char	*gwc;
	char	*p;
	size_t	size;

	envp = (*env);
	path = NULL;
	size = 0;
	p = last_slash(command);
	cd_error(command, 1, env);
	cd_next_env(envp, env);
	envp = *env;
	gwc = getcwd(path, size);
	if (gwc != NULL)
		cdnext_norm(envp, command);
	free(gwc);
	free(p);
}

void	cd_next_env(t_env *envp, t_env **env)
{
	while (envp)
	{
		if (!ft_strcmp("OLDPWD", envp->c))
		{
			free(envp->v);
			envp->v = check_env(ft_strdup("PWD"), env);
		}
		envp = envp->next;
	}
}
