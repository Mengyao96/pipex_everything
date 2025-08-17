/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:57:56 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/17 11:59:29 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getenv(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path = ft_strchr(envp[i], '=');
			path++;
			if (path)
				return (path);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strtrunk(char *s, char c)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup(s);
	if (!res)
		return (NULL);
	while (res[i])
	{
		if (res[i] == c)
		{
			res[i] = '\0';
			break;
		}
		i++;
	}
	return (res);
}

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	get_counts(char **cmds)
{
	int	count;

	if (cmds == NULL)
		return (0);
	count = 0;
	while (cmds[count])
		count++;
	return (count);
}
