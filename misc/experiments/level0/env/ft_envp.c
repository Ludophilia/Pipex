#include "includes/pipex.h"

// int	main(int argc, char **argv)
// {
// 	char	**strs;

// 	argc--;
// 	argv++;
// 	strs = ft_split(*argv, ' ');
// 	if (strs == NULL && ft_eprintf("failed to create tab\n"))
// 		return (1);
// 	if (*strs == NULL && ft_eprintf("empty cmd?\n"))
// 		return (2);	
// 	while (*strs)
// 		ft_printf("%s\n", *strs++);
// 	return (0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	while (*envp)
// 		ft_printf("%s\n", *envp++);
// 	return (0);
// }

static int	free_paths(char **strs)
{
	char	**head;

	if (strs == NULL)
		return (-1);
	head = strs;
	while (*head)
	{
		free(*head);
		head++;
	}
	free(strs);
	return (0);
}

// 10/05 - 
char	*build_paths(char const *s1, char const *s2)
{
	size_t	len[2];
	char	*s1s2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	s1s2 = ft_calloc(len[0] + 1 + len[1] + 1, sizeof(char));
	if (s1s2 == NULL)
		return (NULL);
	if (ft_strlcat(s1s2, s1, len[0] + 1) == len[0]
		&& ft_strlcat(s1s2, "/", len[0] + 2) == len[0] + 1
		&& ft_strlcat(s1s2, s2, len[0] + len[1] + 2) == len[0] + len[1] + 1)
		return (s1s2);
	return (NULL);
}

static char	**get_paths(char **envp)
{
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (ft_split(ENV_PATH_DFLT, ':'));
}

int	main(int argc, char **argv, char **envp)
{
	char	*candidate;
	char 	**paths;
	int		i;

	if (argc != 2 && ft_eprintf("One argument please\n"))
		return (1);
	paths = get_paths(envp);
	if (paths == NULL && ft_eprintf("err 2\n"))
		return (2);
	i = -1;
	while (paths[++i])
	{
		candidate = build_paths(paths[i], argv[1]);
		if (candidate == NULL && free_paths(paths) == -1 && ft_eprintf("err 3\n")) // free paths
			return (3);
		printf("Testing \"%s\"...\n", candidate);
		if (access(candidate, X_OK) == 0)
		{
			ft_printf("\"%s\" is a valid path.\n", candidate);
			free(candidate);
			free_paths(paths);
			return (0);
		}
		free(candidate);
	}
	ft_printf("No valid path have been found.\n");
	free_paths(paths);
	return (0);
}
