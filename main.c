/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:55:07 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/18 22:10:39 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//./pipex      file1    cmd1    cmd2      file2
// access : F_OK. R_OK, W_OK. X_OK




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
		return (perror("argc"), 0);
	if (envp == NULL)
		return (perror("envp"), 0);


	if (argv_check(argv, fd, &cmds, envp) == 0)
		return (0);


	exit_code = run_prcs(argv, envp, fd, cmds);
	if (exit_code < 0)
	{
		free_array(cmds);
		return (perror("run_prcs"), 0);
	}

	free_array(cmds);
	return (0);
}

