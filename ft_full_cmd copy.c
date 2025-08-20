/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_full_cmd copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:23:41 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/20 20:28:15 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	char	*pos;
	char	*parsed_str;

	start = *str + 1;
	if (c == '\'')
	{
		end = ft_strchr(start, c);
		if (!end)
			return (NULL);
		parsed_str = ft_substr(start, 0, end - start);
		if (!parsed_str)
			return (NULL);
		*str = end + 1;
	}
	else
	{
		end = start;
		parsed_str = malloc(sizeof(char) * (ft_strlen(start) + 1));
		if (!parsed_str)
			return (NULL);
		pos = parsed_str;
		while (*end && *end != '"')
		{
			if (*end == '\\' && *(end + 1) == '"')
			{
				*pos++ = *(end + 1);
				end += 2;
			}
			else
				*pos++ = *end++;
		}
		if (*end != '"')
			return (free(parsed_str), NULL);
		*pos = '\0';
		*str = end + 1;
	}
	args = ft_add_to_array(args, parsed_str);
	return (args);
}


char	**handle_normal(char **args, char **str)
{
	char	*end;
	char	*pos;
	char	*parsed_str;

	end = *str;
	parsed_str = malloc(sizeof(char) * (ft_strlen(end) + 1));
	if (!parsed_str)
		return (NULL);
	pos = parsed_str;
	while (*end && *end != ' ')
	{
		if (*end == '\\' && *(end + 1))
		{
			*pos++ = *(end + 1);
			end += 2;
		}
		else
			*pos++ = *end++;
	}
	*pos = '\0';
	*str = end;
	args = ft_add_to_array(args, parsed_str);
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

// void leaks(void)
// {
//  system("leaks a.out");
// }

// int	main()
// {
// 	char	**cmds;
// 	char	*str;

// 	atexit(leaks);
// 	str =  "awk '{count++} END {print count}'";//./script\"quote.sh";
// 	cmds = ft_full_cmd(str);
// 	int i = 0;
// 	while (cmds[i])
// 	{
// 		printf(">>cmds[%d] = %s\n", i, cmds[i]);
// 		i++;
// 	}
// 	printf(">>>cmds[%d] = %s\n",i, cmds[i]);
// 	free_array(cmds);
// 	return (0);
// }
