/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:40:25 by likong            #+#    #+#             */
/*   Updated: 2024/09/17 13:58:28 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	compare_key(t_env *env, char *key)
{
	return (ft_strcmp(env->key, key) == 0);
}

void	ft_unset(char **args)
{
	int	i;

	i = -1;
	// if (matrix_size(args) == 1)
	// {
	// 	ft_putstr_fd("minishell: unset: not enough arguments\n", 2);
	// 	ms()->exit = 1;
	// 	return ;
	// }
	while (args[++i])
	{
		ft_list_remove_if(&ms()->env_list, args[i], compare_key, delete_env);
		ft_list_remove_if(&ms()->local_var, args[i], compare_key, delete_env);
	}
	ms()->exit = 0;
}
