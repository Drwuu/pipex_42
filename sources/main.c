/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:15:52 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/21 19:16:01 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_datas	datas;

	datas = init_datas(ac, av, envp);
	if (ac < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (-1);
	}
	if (ft_strncmp("here_doc", av[1], 8) == 0)
		heredoc(&datas, av[2]);
	else
	{
		datas.outfile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (datas.outfile_fd == -1)
			error("open error");
		datas.infile_fd = open(av[1], O_RDONLY, 0777);
		if (datas.infile_fd == -1)
			error("open error");
		if (dup2(datas.infile_fd, STDIN_FILENO) == -1)
			error("dup2 error");
	}
	execute_commands(&datas);
	return (0);
}
