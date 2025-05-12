/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:48:43 by jegerman          #+#    #+#             */
/*   Updated: 2025/05/12 20:03:51 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ptb_load_env_paths(char **envp)
{
	char	**paths;
	int		is_default;
	
	is_default = 1;
	while (*envp)
		if (ft_strnstr(*envp++, "PATH", 4) && is_default--)
			break ;
	if (is_default)
		paths = ft_split(DEFAULT_PATH, ':');
	else
		paths = ft_split(*envp + 5, ':');
	return (paths);
}

static char	*ptb_build_path(char **strs)
{
	char	*path;
	int		path_len;
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

int	ptb_check_path(char **cmd_args, t_prg *prgs, int i, char **envp)
{
	char	**paths;
	char	*new_path;
	int		i;

	if (**cmd_args == '/')
		return (fmg_access(*cmd_args, X_OK));
	paths = ptb_load_env_paths(envp);
	if (paths == NULL)
		return (-1);
	i = -1;
	while (paths[++i])
	{
		new_path = ptb_build_path((char *[]){paths[i], "/", cmd_args[0], 0});
		if (new_path == NULL && pgm_free_strs(paths, 0))
			return (-1);
		if (access(new_path, X_OK) == 0 && pgm_free_strs(paths, 0))
		{
			free(*cmd_args);
			*cmd_args = new_path;
			return (0);
		}
		free(new_path);
	}
	(ft_eprintf(ERR_CMD, *cmd_args), pgm_free_strs(paths, 0));
	return (-1);
}
