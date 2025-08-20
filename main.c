/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:55:07 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/20 20:29:55 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void leaks(void)
{
 system("leaks a.out");
}


int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	char	**cmds;
	int		exit_code;

	// atexit(leaks);
	if (argc < 5)
		return (perror("argc"), 1);

	get_fd(argv, argc, fd);
	cmds = get_cmds(argv, argc);
	if (!cmds)
		return (perror("get_cmds"), 1);

	exit_code = run_prcs(argv, envp, fd, cmds);
	if (exit_code < 0)
	{
		free_array(cmds);
		return (perror("run_prcs"), 1);
	}
	free_array(cmds);
	return (exit_code);
}

