/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norm5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:29:37 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/23 21:52:45 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialination(t_exec **n, t_exec *exec_val)
{
	(*n) = exec_val;
	(*n)->infile = STDIN_FILENO;
	(*n)->outfile = STDOUT_FILENO;
	(*n)->flag = 0;
	(*n)->flag2 = 0;
	(*n)->flag3 = 0;
}

void	initialination2(t_var2 *vars)
{
	vars->i = 0;
	vars->len = 0;
	vars->s = 0;
}

int	initialination3(t_list **head, t_exec **n, t_exec **exec_val, t_env **envp)
{
	if ((*head)->sep_type == 1)
		exec_norm(head, n);
	else if ((*head)->sep_type == 2)
	{
		if (exec_norm4(head, n) == -1)
		{
			printf_error2(&(*head)->command[0], envp);
			(*envp)->es = 1;
			return (-1);
		}
	}
	else if ((*head)->sep_type == 3)
		exec_norm5(head, n);
	else if ((*head)->sep_type == 5)
		exec_norm6(head, n, exec_val);
	else if ((*head)->type == 'W')
		exec_norm2(head, n);
	else if ((*head)->sep_type == 4)
		exec_norm7(n);
	return (0);
}
