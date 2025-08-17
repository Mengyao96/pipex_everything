/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 20:06:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/17 20:19:53 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

// input functions
char	*ft_strtrunk(char *s, char c);
void	free_array(char **array);
char	*get_path(char *path, char *cmd);
char	*ft_getenv(char **envp);
// char	**ft_full_cmd(char *str);
int		argv_check(char **argv, int fd[2], char ***cmds, char **envp);

int	run_prcs(char **argv, char **envp, int fd[2], char **cmds);
int	get_counts(char **cmds);
#endif
