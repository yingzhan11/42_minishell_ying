/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:37:16 by likong            #+#    #+#             */
/*   Updated: 2024/08/29 19:34:34 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node(t_list **list, char *str)
{
	int		i;
	char	*key;
	char	*value;

	i = str_len(str, "=");
	key = ft_substr(str, 0, i);
	value = ft_strdup(str + i + 1);
	ft_lstadd_front(list, ft_lstnew(new_env(key, value)));
}

t_list	*init_list(char **strs)
{
	t_list	*list;
	int		i;

	i = matrix_size(strs);
	list = NULL;
	while (--i >= 0)
		add_node(&list, strs[i]);
	return (list);
}

char	**list_to_arr(t_list *list)
{
	int		i;
	char	*res1;
	char	*res2;
	char	**strs;
	t_env	*env;

	strs = (char **)malloc((ft_lstsize(list) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	i = -1;
	while (list)
	{
		env = (t_env *)list->content;
		res1 = ft_strjoin(env->key, "=");
		res2 = ft_strjoin(res1, env->value);
		strs[++i] = ft_substr(res2, 0, ft_strlen(res2));
		ft_free(res1);
		ft_free(res2);
		list = list->next;
	}
	strs[++i] = NULL;
	return (strs);
}
