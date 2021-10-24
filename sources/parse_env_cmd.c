/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:49:16 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/24 13:32:57 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_env_path(char **envp)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (envp[++i])
	{
		path = ft_find_str_in_str(envp[i], "PATH=");
		if (path)
		{
			path = ft_substr(path, 5, ft_strlen(path));
			if (!path)
				error("Error");
			return (path);
		}
	}
	return (NULL);
}

char	**get_env_paths(char **envp)
{
	char	*env_path;
	char	**paths;
	int		i;

	i = -1;
	env_path = find_env_path(envp);
	paths = ft_split(env_path, ":");
	wrfree(env_path);
	if (!paths)
		ft_error(NULL, (void **)paths, NULL, "ft_split failed or "
			"error occured getting environment paths");
	return (paths);
}

char	*get_binary(char *cmd, char **env_parsed)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = -1;
	cmd_path = NULL;
	tmp = NULL;
	while (env_parsed[++i])
	{
		tmp = ft_strjoin(env_parsed[i], "/");
		if (!tmp)
			ft_error(cmd_path, (void **)env_parsed, NULL, "tmp join failed");
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			ft_error(tmp, (void **)env_parsed, NULL, "cmd_path join failed");
		wrfree(tmp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		wrfree(cmd_path);
	}
	if (cmd_path)
		wrfree(cmd_path);
	ft_error(tmp, (void **)env_parsed, NULL, "an error occured getting "
		"binaries");
	return (NULL);
}
