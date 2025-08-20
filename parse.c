/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:27:03 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/20 10:50:36 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_fd(char **argv, int argc, int fd[2])
{
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] < 0)
	{
		perror("pipex: input");
		fd[0] = open("/dev/null", O_RDONLY);
	}

	fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] < 0)
	{
		perror(argv[argc - 1]);
		exit(EXIT_FAILURE);
	}
}

char	**get_cmds(char **argv, int argc)
{
	int		i;
	char	**cmds;

	cmds = malloc(sizeof(char *) * (argc - 3 + 1));
	if (cmds == NULL)
		perror("malloc");
	i = 0;
	while (i < argc - 3)
	{
		if (ft_strchr(argv[2 + i], '/'))
		{
			cmds[i] = argv[2 + i];

		}
		else
			cmds[i] = ft_strtrunk(argv[2 + i], ' ');
		i++;
	}
	cmds[argc - 3] = NULL;
	return (cmds);
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

