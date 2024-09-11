/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:44:05 by likong            #+#    #+#             */
/*   Updated: 2024/09/11 12:47:49 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// May need change later
static void	exec_others(char **cmds)
{
	char		*path;
	struct stat	path_stat;

	path = get_path(cmds[0]);
	stat(path, &path_stat);
	if (path)
	{
		if (S_ISDIR(path_stat.st_mode))
			ft_putstr_fd("error 1\n", 2);
		else if (S_ISREG(path_stat.st_mode))
		{
			execve(path, cmds, ms()->envp);
			ft_putstr_fd("error 2\n", 2);
		}
		ft_free(path);
	}
	else
		ft_putstr_fd("error 3\n", 2);
	return ;
}

static void	handle_command(char **cmds)
{
	if (!is_builtin(cmds[0]))
		exec_others(cmds);
	if (!ft_strcmp(cmds[0], "exit") && ms()->cmd_nb == 1)
		ft_exit(cmds);
	else if (!ft_strcmp(cmds[0], "pwd") && matrix_size(cmds) == 1)
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp(cmds[0], "env") && matrix_size(cmds) == 1)
		print_env();
}

//missed signal function
static pid_t	handle_child(t_ast *node)
{
	pid_t	pid;

	signal_child();
	pid = fork();
	if (pid < 0)
		show_error(NULL, FORK, FAIL_STD);
	else if (pid == 0)
	{
		if (ms()->in_fd == -1 || ms()->out_fd == -1)
			restart(true);
		if (ms()->in_fd == STD_IN)
			if (node->index != 0)
				ms()->in_fd = ms()->fds[node->index - 1][READ];
		if (ms()->out_fd == STD_OUT)
			if (node->index < ms()->cmd_nb - 1)
				ms()->out_fd = ms()->fds[node->index][WRITE];
		dup_fd();
		handle_command(node->arg);
		restart(true);
	}
	close_fd(node->index);
	return (pid);
}

static pid_t	fill_pipe(t_ast *node)
{
	pid_t	pid;

	pid = 0;
	if (!node)
		return (pid);
	pid = fill_pipe(node->left);
	pid = fill_pipe(node->right);
	if (!is_redir_or_pipe(node->token))
	{
		if (is_unfork(node->arg[0], node->arg[1]) || ms()->cmd_nb < 2)
			handle_command(node->arg);
		else
			pid = handle_child(node);
	}
	else if (is_redir(node->token) && node->arg)
		redirect(node->token->type, node->arg[0]);
	return (pid);
}

//missed signal function
void	execute(t_ast *ast)
{
	pid_t	pid;
	int		status;

	status = 0x7F;
	create_pipe();
	pid = fill_pipe(ast);
	pid = waitpid(pid, &status, 0);
	while (waitpid(0, NULL, 0) > 0)
		continue ;
	if (WIFEXITED(status))
		ms()->exit = WEXITSTATUS(status);
	signal_default();
}
