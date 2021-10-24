/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:31:27 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/23 20:43:19 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_datas	init_datas(int ac, char **av, char **envp)
{
	t_datas	datas;

	datas.ac = ac;
	datas.av = av;
	datas.envp = envp;
	datas.infile_fd = 0;
	datas.outfile_fd = 0;
	datas.p_fd[0] = 0;
	datas.p_fd[1] = 0;
	datas.is_heredoc = FALSE;
	return (datas);
}

void	error(const char *error)
{
	perror(error);
	wrdestroy();
	exit(EXIT_FAILURE);
}
