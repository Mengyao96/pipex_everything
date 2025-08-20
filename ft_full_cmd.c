/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_full_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:23:41 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/20 09:20:25 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//awk '{count++} END {print count}'
//grep -v \"u y\"
//echo \"a \\\"quoted\\\" b\"
//./script"quote.sh
//./script.sh arg1 \"a b\" 'c d' plain\\ space \"x\\\"y\"


char	**ft_add_to_array(char **arr, char *str)
{
	char	**new_arr;
	int		counts;
	int		i;

	counts = 0;
	if (arr)
		counts = get_counts(arr);
	new_arr = malloc(sizeof(char *) * (counts + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < counts)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = str;
	new_arr[i + 1] = NULL;
	if (arr)
		free(arr);
	return (new_arr);
}

char	**handle_quotes(char **args, char **str, char c)
{
	char	*start;
	char	*end;

	start = *str + 1;
	end = ft_strchr(start, c);
	if (!end)
		return (NULL);
	args = ft_add_to_array(args, ft_substr(start, 0, end - start));
	if (!args)
		return (NULL);
	*str = end + 1;
	return (args);
}

char	**handle_normal(char **args, char **str)
{
	char	*start;
	char	*end;

	start = *str;
	end = start;
	while (*end && *end != ' ' && *end != '\'' && *end != '\"')
		end++;
	args = ft_add_to_array(args, ft_substr(start, 0, end - start));
	if (!args)
		return (NULL);
	*str = end;
	return (args);
}

char	**ft_full_cmd(char *str)
{
	char	**args;

	args = NULL;
	while (*str)
	{
		while (*str == ' ')
			str++;
		if (!*str)
			break;
		if (*str == '\'' || *str == '\"')
		{
			args = handle_quotes(args, &str, *str);
			if (!args)
				return (NULL);
		}
		else
		{
			args = handle_normal(args, &str);
			if (!args)
				return (NULL);
		}
	}
	return (args);
}


// char	**ft_full_cmd(char *str)
// {

// 	return (free(segs[0]), free(segs[1]), curr_cmd);
// }


/* void leaks(void)
{
 system("leaks a.out");
}


int	main()
{
	char	**cmds;
	char	*str;

	atexit(leaks);
	str =  "grep Now" ;//"awk '{count++} END {print count}'";//./script\"quote.sh";//"echo -g -t 'a \"qu \"plus\" oted\" b'";
	cmds = ft_full_cmd(str);
	int i = 0;
	while (cmds[i])
	{
		printf(">>cmds[%d] = %s\n", i, cmds[i]);
		i++;
	}
	printf(">>>cmds[%d] = %s\n",i, cmds[i]);
	free_array(cmds);
	return (0);
} */
