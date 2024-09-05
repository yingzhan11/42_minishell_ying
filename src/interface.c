/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:37:11 by likong            #+#    #+#             */
/*   Updated: 2024/09/05 12:57:08 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_prompt(void)
{
	char	*res1;
	char	*res2;

	res1 = ft_strjoin("minishell:", ms()->cwd);
	if (!res1)
		return (NULL);
	res2 = ft_strjoin(res1, "$ ");
	if (!res2)
	{
		ft_free(res1);
		return (NULL);
	}
	ft_free(res1);
	return (res2);
}

// void print_ast_arg(t_ast *node)
// {
//     if (node == NULL)
//         return;
//     int j = 0;
//     while (node->arg && node->arg[j])
//     {
//         printf("parser: %s\n", node->arg[j]);
//         j++;
//     }
//     print_ast_arg(node->left);
//     print_ast_arg(node->right);
// }

/*void	pre_handle(void)
{
//lexer
    if (!check_quote())
        return ;
    lexer();
	if (!check_syntax())
		return ;
	//lexer test
    // t_list *cur;
    // cur = ms()->lexer_tk;
    // while (cur)
    // {
    //     printf("input: %s\n", ((t_token *)(cur->content))->input);
	// 	printf("can merge: %i\n", ((t_token *)(cur->content))->mergeable);
    //     cur = cur->next;
    // }
	
//expander
	expander();
	//test expander
	// t_list *exp;
    // exp = ms()->lexer_tk;
    // while (exp)
    // {
	// 	printf("expander: %s\n", ((t_token *)(exp->content))->input);
    //     exp = exp->next;
    // }

//parser
	parser();
	//test parse
	// t_ast *ast = ms()->ast;
    // print_ast_arg(ast);

    return ;
}*/

void	pre_handle(void)
{
	if (!check_quote())
		return ;
	lexer();
	if (!check_syntax())
		return ;
	expander();
	parser();
	return ;
}

void	start_shell(void)
{
	while (1)
	{
		ms()->prompt = set_prompt();
		ms()->input = readline(ms()->prompt);
		if (!ms()->input)
		{
			write(1, "exit\n", 5);
			restart(true);
		}
		add_history(ms()->input);
		pre_handle();
	//check assignment, execute, update_env
		//execute();
		restart(false);
	}
	rl_clear_history();
}
