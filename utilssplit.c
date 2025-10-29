/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilssplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:51:43 by abensaid          #+#    #+#             */
/*   Updated: 2025/10/29 19:56:59 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*start_end(const char *s, int pos, char c)
{
	char	*word;
	int		start;
	int		end;
	int		j;

	j = 0;
	start = pos;
	while (s[pos] && s[pos] != c)
		pos++;
	end = pos;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[j++] = s[start++];
	word[j] = '\0';
	return (word);
}

void	free_tab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	tab = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			tab[j] = start_end(s, i, c);
			if (!tab[j])
				return (free_tab(tab, j - 1), NULL);
			j++;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}