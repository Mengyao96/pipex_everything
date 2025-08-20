/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:01:42 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/20 21:25:12 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_false_exit(void)
{
	if (errno == ENOENT)
		exit(127);
	else
		exit(126);
}

void	init_pipes(int pipes[2])
{
	pipes[0] = -1;
	pipes[1] = -1;
}
