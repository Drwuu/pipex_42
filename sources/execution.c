/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 11:41:12 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/24 13:32:29 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	main_execution(char *av, char **envp)
{
	char	**env_paths;
	char	**cmd;
	char	*binary;

	cmd = ft_split(av, " ");
	if (!cmd)
		ft_error(NULL, (void **)cmd, NULL, "ft_split failed or "
			"error occured getting command or command options");
	env_paths = get_env_paths(envp);
	binary = get_binary(cmd[0], env_paths);
	ft_free_dbl_array((void **)env_paths, 0);
	if (!binary)
		ft_error(NULL, (void **)env_paths, NULL, "An error occured getting "
			"binary file");
	if (execve(binary, cmd, envp) == -1)
	{
		wrfree(binary);
		ft_free_dbl_array((void **)env_paths, 0);
		ft_free_dbl_array((void **)cmd, 0);
		error("Error");
	}
}

static void	child(char *cmd, char **envp, int *fd_pipe)
{
	if (close(fd_pipe[0]) == -1)
		error("Error");
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		return (error("Error"));
	main_execution(cmd, envp);
}

static void	parent(int *fd_pipe, pid_t *pid)
{
	if (close(fd_pipe[1]) == -1)
		error("Error");
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		error("Error");
	if (waitpid(*pid, NULL, 0) == -1)
		error("Error");
	if (close(fd_pipe[0]) == -1)
		error("Error");
	wrdestroy();
}

static void	pipex(char *cmd, char **envp)
{
	int		fd_pipe[2];
	pid_t	pid;

	if (pipe(fd_pipe) == -1)
		error("Error");
	pid = fork();
	if (pid == -1)
		error("Error");
	if (pid == 0)
		child(cmd, envp, fd_pipe);
	else
		parent(fd_pipe, &pid);
}

void	execute_commands(t_datas *datas)
{
	int	i;

	i = 1;
	if (datas->is_heredoc)
		i = 2;
	while (++i < datas->ac - 2)
		pipex(datas->av[i], datas->envp);
	if (dup2(datas->outfile_fd, STDOUT_FILENO) == -1)
		ft_error(NULL, NULL, NULL, "dup2 failed");
	main_execution(datas->av[datas->ac - 2], datas->envp);
}
