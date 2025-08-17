/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 22:55:07 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/17 18:39:52 by mezhang          ###   ########.fr       */
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
	int		check;

	// atexit(leaks);
	if (argc < 5)
		return (perror("argc"), exit(EXIT_FAILURE), 0);
	if (envp == NULL)
		return (perror("envp"), exit(EXIT_FAILURE), 0);

	check = argv_check(argv, fd, &cmds, envp);
	if (check == 0)
		return (free_array(cmds), free(fd), perror("argv_check"), exit(EXIT_FAILURE), 0);


	check = run_prcs(argv, envp, fd, cmds);
	if (check == 0)
	{
		free_array(cmds);
		return (perror("run_prcs"), exit(EXIT_FAILURE), 0);
	}

	free_array(cmds);
	return (0);
}

