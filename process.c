/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:56:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/20 19:54:12 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_pr(int i, int *pre_fd, int *pipes, int fd[2])
{

	if (*pre_fd != STDIN_FILENO)
	{
		dup2(*pre_fd, STDIN_FILENO);
		close(*pre_fd);
	}
	if (i == 0)
		dup2(pipes[1], STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);

	if (pipes[0] != -1)
		close(pipes[0]);
	if (pipes[1] != -1)
		close(pipes[1]);

}


void	child_exe(char **argv, char **envp, int i)
{
	char	**curr_cmd;
	char	*path;
	int		is_path_malloced;

	curr_cmd = ft_full_cmd(argv[i + 2]);
	if (!curr_cmd)
		return (ft_putstr_fd("pipex: malloc failed\n", 2), exit(1));
	is_path_malloced = 0;
	if (ft_strchr(curr_cmd[0], '/'))
		path = curr_cmd[0];
	else
	{
		path = get_path(ft_getenv(envp), curr_cmd[0]);
		is_path_malloced = 1;
	}
	if (!path)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(curr_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_array(curr_cmd);
		exit(127);
	}
	execve(path, curr_cmd, envp);
	perror("execve");
	if (is_path_malloced)
		free(path);
	free_array(curr_cmd);
	if (errno == ENOENT)
		exit(127);
	else
		exit(126);
}

void	parent_pr(int *pre_fd, int *pipes, int i)
{

	if (*pre_fd != STDIN_FILENO && *pre_fd != -1)
	{
		close(*pre_fd);
	}
	if (i == 0)
	{
		close(pipes[1]);
		*pre_fd = pipes[0];
	}
	else
	{
		*pre_fd = -1;
	}
}

int	wait_for_child(pid_t *pids, int total)
{
	int	status;
	int	exit_code;
	int	i;
	int	current;

	i = 0;
	exit_code = 0;
	while (i < total)
	{
		current = waitpid(pids[i], &status, 0);
		if (current == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = WTERMSIG(status);
		i++;
	}
	return (exit_code);
}

int	run_prcs(char **argv, char **envp, int fd[2], char **cmds)
{
	int		pre_fd;
	int		pipes[2];
	pid_t	*pids;
	int		i;

	pre_fd = fd[0];
	i = 0;
	pids = malloc(sizeof(pid_t) * get_counts(cmds));
	if (!pids)
		return (perror("malloc"), -1);
	while (cmds[i])
	{
		if (pipe(pipes))
			pipes[0] = pipes[1] = -1;
		pids[i] = fork();
		if (pids[i] == 0)
		{
			child_pr(i, &pre_fd, pipes, fd);
			child_exe(argv, envp, i);
		}
		else if (pids[i] > 0)
			parent_pr(&pre_fd, pipes, i);
		i++;
	}
	i = wait_for_child(pids, get_counts(cmds));
	return (close(fd[0]), close(fd[1]), free(pids), i);
}

