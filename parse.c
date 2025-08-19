/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:27:03 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/19 09:07:13 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_fd(char **argv, int argc, int fd[2])
{
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] < 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		perror(": ");
		fd[0] = open("/dev/null", O_RDONLY);
	}

	fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] < 0)
	{
		perror(argv[argc - 1]);
	}
}

char	*get_path(char *path, char *cmd)
{
	char	*new_path;
	char	*tmp;
	char	**paths;
	int		i;

	if (path == NULL || cmd == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (tmp == NULL)
			return (free_array(paths), NULL);

		new_path = ft_strjoin(tmp, cmd);
		if (new_path == NULL)
			return (free(tmp), free_array(paths), NULL);
		free(tmp);
		if (access(new_path, X_OK) == 0)
			return (free_array(paths), new_path);
		free(new_path);
		i++;
	}
	return(free_array(paths), NULL);
}

int	get_cmds(char **argv, char **cmds, char **envp)
{
	int		i;
	int		count;
	char	*path;

	count = get_counts(argv) - 3; //deduct a.out file1 file2
	i = 0;
	while (i < count)
	{
		cmds[i] = ft_strtrunk(argv[2 + i], ' ');
		if (ft_strchr(cmds[i], '/'))
		{
			if (access(cmds[i], X_OK) == 0)
				return (1);
		}
		path = get_path(ft_getenv(envp), cmds[i]);
		if (path == NULL)
			return (0);
		free(path);
		i++;
	}
	cmds[count] = NULL;
	return (1);
}

//malloc
int	argv_check(char **argv, int fd[2], char ***cmds, char **envp)
{
	int		argc;

	argc = get_counts(argv);
	get_fd(argv, argc, fd);

	*cmds = malloc(sizeof(char *) * (argc - 3 + 1));
	if (*cmds == NULL)
		return (perror("malloc"), 0);

	if (get_cmds(argv, *cmds, envp) == 0)
		return (perror("get_cmds"), free_array(*cmds), 0);

	return (1);
}
