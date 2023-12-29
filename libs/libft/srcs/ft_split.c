/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshehata <mshehata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:29:29 by mshehata          #+#    #+#             */
/*   Updated: 2023/02/07 13:18:30 by mshehata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static void	make_words(char **words, char const *s, char c, size_t n_words)
{
	char	*ptr_c;

	while (*s && *s == c)
		s++;
	while (n_words--)
	{
		ptr_c = ft_strchr(s, c);
		if (ptr_c != NULL)
		{
			*words = ft_substr(s, 0, ptr_c - s);
			while (*ptr_c && *ptr_c == c)
				ptr_c++;
			s = ptr_c;
		}
		else
			*words = ft_substr(s, 0, ft_strlen(s) + 1);
		words++;
	}
	*words = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		num_words;
	char	**words;

	if (s == NULL)
		return (NULL);
	num_words = count_words(s, c);
	words = malloc(sizeof(words) * (num_words + 1));
	if (words == NULL)
		return (NULL);
	make_words(words, s, c, num_words);
	return (words);
}

// int main (void)
// {
// 	char s[] = "asdas";
// 	char d = 0;
// 	int i = 0;
// 	char **array = ft_split(s, d);

// 	while (i < 2)
// 	{
// 		printf("Word[%d] : %s\n", i, array[i]);
// 		i++;
// 	}
// }
