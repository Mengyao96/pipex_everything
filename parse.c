/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:27:03 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/17 18:58:44 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_fd(char **argv, int fd[2])
{
	if (access(argv[1], F_OK) == -1)
		return (fprintf(stderr, "pipex: input: command not found\n"), exit(0), 0);

	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
		return (perror("open"), exit(EXIT_FAILURE), 0);

	fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
		return (perror("open"), exit(EXIT_FAILURE), 0);
	return (1);
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
	cmds[count--] = NULL; //last element should be NULL
	while (count >= 0)
	{
		cmds[count] = ft_strtrunk(argv[2 + count], ' ');
		if (cmds[count] == NULL)
			return (free_array(cmds), fprintf(stderr, "pipex: %s: command not found\n", cmds[count]), exit(127), 0);
		count--;
	}

	i = 0;
	while (i < 2)
	{
		path = get_path(ft_getenv(envp), cmds[i]);
		if (path == NULL)
			return (0);
		if (access(path, X_OK) == -1)
			return (free(path), perror("msg"), exit(EXIT_FAILURE), 0);
		free(path);
		i++;
	}
	return (1);
}

//malloc
int	argv_check(char **argv, int fd[2], char ***cmds, char **envp)
{
	int		check;

	check = get_fd(argv, fd);
	if (check == 0)
		return (free(fd), perror("get_fd"), exit(EXIT_FAILURE), 0);

	*cmds = malloc(sizeof(char *) * (get_counts(argv) - 3 + 1));
	if (*cmds == NULL)
		return (perror("malloc"), 0);
	if (get_cmds(argv, *cmds, envp) == 0)
		return (exit(127), 0);

	return (1);
}
