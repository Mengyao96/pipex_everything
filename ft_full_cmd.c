/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_full_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:23:41 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/17 21:12:06 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//awk '{count++} END {print count}'
//grep -v \"u y\"
//echo \"a \\\"quoted\\\" b\"
//./script"quote.sh
//./script.sh arg1 \"a b\" 'c d' plain\\ space \"x\\\"y\"



char	**ft_realloc(char **arr, int new_size)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * (new_size + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new_arr[i] = arr[i];
		i++;
	}
	free(arr);
	new_arr[i] = NULL;
	return (new_arr);
}

char	*get_quote(char *s)
{
	char	*start;
	char	*end;
	char	*quote;
	char	c;

	start = ft_strchr(s, '\"');
	if (!start || (ft_strchr(s, '\'') && ft_strchr(s, '\'') < start))
		start = ft_strchr(s, '\'');
	if (!start)
		return (NULL);
	c = *start;
	end = ft_strrchr(start + 1, c);
	if (!end)
		return (NULL);
	quote = malloc(sizeof(char) * (end - start));
	if (!quote)
		return (NULL);
	ft_strlcpy(quote, start + 1, end - start);
	return (quote);
}


char	**ft_full_cmd(char *str)
{
	char	**curr_cmd;
	char	*quote;
	int		i;
	char	*segs[2];
	char	q;

	i = 0;
	while (str[i] != '\'' && str[i] != '\"' && str[i] != '\0')
		i++;
	segs[0] = ft_substr(str, 0, i);
	printf("segs[0] = %s\n", segs[0]);
	segs[1] = ft_substr(str, i, ft_strlen(str) - i);
	printf("segs[1] = %s\n", segs[1]);

	curr_cmd = ft_split(segs[0], ' ');
	if (!curr_cmd)
		return (free(segs[0]), free(segs[1]), NULL);
	quote = get_quote(segs[1]);
	i = get_counts(curr_cmd);
	if (quote)
	{
		curr_cmd = ft_realloc(curr_cmd, i + 1);
		if (!curr_cmd)
			return (free_array(curr_cmd), NULL);
		curr_cmd[i] = ft_strdup(quote);
		free(quote);
		curr_cmd[i + 1] = NULL;
	}
	return (free(segs[0]), free(segs[1]), curr_cmd);
}


// void leaks(void)
// {
//  system("leaks a.out");
// }




int	main()
{
	char	**cmds;
	char	*str;


	// atexit(leaks);
	str = "./script\"quote.sh";//"echo -g -t 'a \"qu \"plus\" oted\" b'";
	cmds = ft_full_cmd(str);
	if (!cmds)
	{
		perror("ft_full_cmd");
		exit (127);
	}
	int i = 0;
	while (cmds[i])
	{
		printf(">>cmds[%d] = %s\n", i, cmds[i]);
		i++;
	}
	printf(">>>cmds[%d] = %s\n",i, cmds[i]);
	free_array(cmds);
	return (0);
}

