/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshehata <mshehata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:03:00 by mshehata          #+#    #+#             */
/*   Updated: 2023/01/15 10:23:23 by mshehata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*needle == 0 || haystack == needle)
		return ((char *)haystack);
	if (!len)
		return (NULL);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j] && i + j < len)
			{
				if (needle[j + 1] == '\0')
					return ((char *)haystack + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char *haystack = "This is my test phrase";
// 	char needle[] = "is m";
// 	char *res = ft_strnstr(haystack, needle, 3);
// 	if (res == NULL)
// 		printf("NULL\n");
// 	else
// 		printf("%s\n", res);
// }
