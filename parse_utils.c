/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:57:56 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/20 20:55:21 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_default_path(void)
{
	char	*default_path;
	char	**envp;

	default_path = ft_strdup("PATH=/Users/mezhang/goinfre/homebrew/bin:/usr/\
		local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/\
		Apple/usr/bin:/Library/Frameworks/Mono.framework/Versions/Current\
		Commands");
	if (!default_path)
		return (NULL);
	envp = ft_add_to_array(NULL, default_path);
	if (!envp)
		return (free(default_path), NULL);
	return (envp);
}

char	*ft_getenv(char **envp)
{
	int		i;
	char	*path;
	int		is_default;

	i = 0;
	is_default = 0;
	if (!envp || !*envp)
	{
		envp = ft_default_path();
		is_default = 1;
	}
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
	if (is_default)
		free_array(envp);
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
			break ;
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
