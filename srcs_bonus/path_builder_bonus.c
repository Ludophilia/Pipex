/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_builder_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:48:43 by jegerman          #+#    #+#             */
/*   Updated: 2025/05/16 20:22:12 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**ptbb_load_env_paths(char **envp)
{
	char	**paths;
	int		is_dflt;
	int		i;

	is_dflt = 1;
	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH", 4) && is_dflt--)
			break ;
	if (is_dflt)
		paths = ft_split(ENV_PATH_DFLT, ':');
	else
		paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

static char	*ptbb_build_path(char **strs)
{
	char	*path;
	size_t	path_len;
	int		i;

	i = 0;
	path_len = 0;
	while (strs[i])
		path_len += ft_strlen(strs[i++]);
	path = ft_calloc(path_len + 1, sizeof(char));
	if (path == NULL)
		return (NULL);
	i = -1;
	while (strs[++i])
	{
		path_len = ft_strlen(path) + ft_strlen(strs[i]);
		if (ft_strlcat(path, strs[i], path_len + 1) != path_len)
		{
			free(path);
			return (NULL);
		}
	}
	return (path);
}

int	ptbb_check_path(char **cmd_args, char **envp)
{
	char	**paths;
	char	*new_path;
	int		i;

	if (ft_strchr(*cmd_args, '/'))
		return (fmgb_access(*cmd_args, X_OK));
	paths = ptbb_load_env_paths(envp);
	if (paths == NULL)
		return (-1);
	i = -1;
	while (paths[++i])
	{
		new_path = ptbb_build_path((char *[]){paths[i], "/", cmd_args[0], 0});
		if (new_path == NULL && pgmb_free_strs(0, paths))
			return (-1);
		if (access(new_path, X_OK) == 0 && pgmb_free_strs(0, paths))
		{
			free(*cmd_args);
			*cmd_args = new_path;
			return (0);
		}
		free(new_path);
	}
	(ft_eprintf(ERR_CMD, *cmd_args), pgmb_free_strs(0, paths));
	return (-1);
}
