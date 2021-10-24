/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 20:11:25 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/24 13:24:21 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char *limiter, int fd[2])
{
	char	*line;
	char	*tmp;

	if (close(fd[0]) == -1)
		error("close error");
	while (TRUE)
	{
		tmp = readline(NULL);
		line = ft_strjoin(tmp, "\n");
		wrfree(tmp);
		if (line && ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			wrfree(line);
			if (close(fd[1]) == -1)
				error("close error");
			wrdestroy();
			exit(EXIT_SUCCESS);
		}
		if (write(fd[1], line, ft_strlen(line)) == -1)
			error("write error");
		if (line)
			wrfree(line);
	}
}

void	parent(pid_t *pid, int fd[2])
{
	if (close(fd[1]) == -1)
		error("close error");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error("dup2 error");
	if (waitpid(*pid, NULL, 0) == -1)
		error("waitpid error");
	if (close(fd[0]) == -1)
		error("close error");
}

void	heredoc(t_datas *datas, char *limiter)
{
	int		fd_pipe[2];
	pid_t	pid;

	if (datas->ac < 6)
		error("./pipex here_doc LIMITER cmd cmd1 file");
	datas->is_heredoc = TRUE;
	datas->outfile_fd = open(datas->av[datas->ac - 1], \
		O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (datas->outfile_fd == -1)
		error("open error");
	if (pipe(fd_pipe) == -1)
		error("pipe error");
	pid = fork();
	if (pid == -1)
		error("fork error");
	if (pid == 0)
		child(limiter, fd_pipe);
	else
		parent(&pid, fd_pipe);
}
