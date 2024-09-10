/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:45:27 by likong            #+#    #+#             */
/*   Updated: 2024/09/10 09:26:30 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_status(char *str)
{
	int	sig;

	sig = 0;
	if (!ft_isnum(str))
		return (1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sig = 1;
		str++;
	}
	if (ft_strlen(str) > 19)
		return (1);
	if (sig)
		return (ft_strcmp(str, "9223372036854775808") > 0);
	else
		return (ft_strcmp(str, "9223372036854775807") > 0);
}

void	ft_exit(char **token)
{
	if (matrix_size(token) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ms()->exit = 1;
		return ;
	}
	if (matrix_size(token) == 2 && check_status(token[1]))
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(token[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ms()->exit = 2;
	}
	else if (matrix_size(token) == 2)
	{
		ft_putstr_fd("exit\n", 1);
		ms()->exit = ft_atoi(token[1]) % 256;
	}
	// matrix_delete(token);
	restart(true);
}
