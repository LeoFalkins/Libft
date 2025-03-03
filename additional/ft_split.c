/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:28:02 by lpolizzi          #+#    #+#             */
/*   Updated: 2025/03/03 13:28:38 by lpolizzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

static bool	is_sep(char c, char *sep)
{
	if (!c)
		return (true);
	while (sep && *sep)
	{
		if (c == *sep)
			return (true);
		sep++;
	}
	return (false);
}

static int	ft_countwords(char *s, char *sep)
{
	int		count;
	bool	in_word;

	count = 0;
	in_word = false;
	while (*s)
	{
		if (is_sep(*s, sep))
			in_word = false;
		else if (!in_word)
		{
			in_word = true;
			count++;
		}
		s++;
	}
	return (count);
}

static void	make_split(char **strs, char *s, char *sep)
{
	int	i;
	int	j;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (is_sep(s[i], sep))
			i++;
		else
		{
			j = 0;
			while (!is_sep(s[i + j], sep))
				j++;
			strs[word] = (char *)malloc(sizeof(char) * (j + 1));
			if (!strs[word])
			{
				free_tab(strs);
				return ;
			}
			ft_strlcpy(strs[word++], s + i, j + 1);
			i += j;
		}
	}
}

char	**ft_split(const char *s, char *sep)
{
	char	**strs;
	int		len;

	if (!s)
		return (NULL);
	len = ft_countwords(s, sep);
	strs = malloc(sizeof(char *) * (len + 1));
	if (!strs)
		return (NULL);
	strs[len] = 0;
	make_split(strs, (char *)s, sep);
	return (strs);
}
