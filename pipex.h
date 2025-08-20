/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 20:06:58 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/20 20:44:48 by mezhang          ###   ########.fr       */
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

// parse functions
void	get_fd(char **argv, int argc, int fd[2]);
char	**get_cmds(char **argv, int argc);
char	*get_path(char *path, char *cmd);
int		get_counts(char **cmds);

// get full commands
char	**ft_add_to_array(char **arr, char *str);
char	**ft_full_cmd(char *str);

// process functions
int	run_prcs(char **argv, char **envp, int fd[2], char **cmds);
int	finish(pid_t **pids, int total, int fd[2]);

#endif
