/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:39:25 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/15 15:18:07 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_substr(char const *s, char c) // *s1 = "awk '{count++} END {print count}'";
{
	int	i;
	int	check;
	int	quote;

	i = 0;
	check = 0;
	quote = 0;
	while (*s)
	{
		if (*s != c && check == 0)
		{
			if ((*s == '\'' || *s == '\"') && quote == 0)
				quote = 1;
			else if ((*s == '\'' || *s == '\"') && quote == 1)
				quote = 0;
			check = 1;
			i++;
		}
		else if (*s == c)
		{
			if (quote != 1)
				check = 0;
		}
		s++;
	}
	return (i);
}


static size_t	substr_len(const char *s, char c)
{
	size_t	i;
	int		q;
	int		check;

	i = q = check = 0;

	if (s[i] == '\'' || s[i] == '\"')
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
		return (i);
	}
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return (i);
}

static char	*get_substr(const char *s, char c)
{
	char	*substr;
	size_t	j;
	size_t	len;

	len = substr_len(s, c);
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	j = 0;
	while (s[j] && j < len)
	{
		if (s[j] == '\'' || s[j] == '\"')
		{
			j++;
			while (s[j] && s[j] != '\'' && s[j] != '\"')
			{
				substr[j - 1] = s[j];
				j++;
			}
			if (s[j])
				j++;
			continue ;
		}
	}
	return (substr[j] = '\0', substr);
}

static void	*free_rest(char **arr, int i)
{
	if (!arr[i])
	{
		while (i--)
		{
			free(arr[i]);
		}
		free(arr);
		return (NULL);
	}
	else
		return (arr[i]);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;

	if (!s)
		return (NULL);

	ptr = (char **)malloc(sizeof(char *) * (count_substr(s, c) + 1));
	if (!ptr)
		return (NULL);
	printf("!!1count_substr: %d\n", count_substr(s, c));
	i = 0;
	while (*s)
	{
		if (*s && *s != c)
		{
			ptr[i] = get_substr(s, c);
			if (!ptr[i])
				return (free_rest(ptr, i), NULL);
			printf("ptr[%d] = %s\n\n", i, ptr[i]);
			s = s + substr_len(s, c);
			if (*s == '\'' || *s == '\"')
			{
				s++;
			}
			i++;
		}
		else
			s++;
	}
	ptr[i] = NULL;
	ft_printf("i = %d\n", i);
	return (NULL);
}

int	main(void)
{
	char const	*s1 = "'{count++} END {print count}'";
	// char		c = 32:' ';
	char		**ptr;
	int			i = 0;

	// printf("count_substr: %d\n", count_substr(s1, ' '));
	// printf("substr_len: %zu\n", substr_len(s1, ' '));
	ptr = ft_split(s1, ' ');
	while (ptr[i] != NULL)
	{
		printf("%s\n", ptr[i]);
		i++;
	}
	while (i - 1 >= 0)
	{
		free(ptr[i - 1]);
		i--;
	}
	free(ptr);
	return (0);
}
