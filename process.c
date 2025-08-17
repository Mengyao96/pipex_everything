/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:56:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/17 19:47:02 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_exe(char **argv, char **envp, int i)
{
	char	**curr_cmd;

	curr_cmd = ft_full_cmd(argv[i + 2]);
	if (!curr_cmd)
	{
		perror("ft_full_cmd");
		exit(127);
	}
	execve(get_path(ft_getenv(envp), curr_cmd[0]), curr_cmd, envp);
	perror("execve");
	free_array(curr_cmd);
	if (errno == ENOENT)
		exit(127);
	else
		exit(126);
}

void	child_pr(int i, int total, int *pre_fd, int *pipes, int fd[2])
{

	if (*pre_fd != STDIN_FILENO)
	{
		dup2(*pre_fd, STDIN_FILENO);
		close(*pre_fd);
	}
	if (i < total - 1)
		dup2(pipes[1], STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);

	if (pipes[0] != -1)
		close(pipes[0]);
	if (pipes[1] != -1)
		close(pipes[1]);

}

void	parent_pr(int *pre_fd, int *pipes, int i, int total)
{

	if (*pre_fd != STDIN_FILENO && *pre_fd != -1)
	{
		close(*pre_fd);
	}
	if (i < total - 1)
	{
		close(pipes[1]);
		*pre_fd = pipes[0];
	}
	else
	{
		*pre_fd = -1;
	}
}


int	run_prcs(char **argv, char **envp, int fd[2], char **cmds)
{
	int		pre_fd;
	int		pipes[] = {-1, -1};
	pid_t	*pids;
	int		i;
	int		total;

	pre_fd = fd[0];
	i = 0;
	total = get_counts(cmds);
	// printf("total = %d\n", total);
	pids = malloc(sizeof(pid_t) * (total));
	if (!pids)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while (cmds[i])
	{
		if (i < total)
		{
			if (pipe(pipes) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		else
			pipes[0] = pipes[1] = -1;

		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pids[i] == 0)
		{
			child_pr(i, total, &pre_fd, pipes, fd);
			child_exe(argv, envp, i);
		}
		else
			parent_pr(&pre_fd, pipes, i, total);
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	while (i > 0)
		waitpid(pids[--i], NULL, 0);
	free(pids);
	return (1);
}
