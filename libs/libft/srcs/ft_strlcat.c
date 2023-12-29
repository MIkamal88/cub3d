/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshehata <mshehata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:02:57 by mshehata          #+#    #+#             */
/*   Updated: 2022/11/25 09:34:57 by mshehata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!dst && !size)
		return (0);
	while (dst[i] && i < size)
		i++;
	while (src[j] && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}

// int	main(void)
// {
// 	//returns array size of dst + src
// 	//adds src TO dst and adds a null terminator after.
// 	char	dst[30] = "This is ";
// 	char	src[] = "my test phrase.";
// 	printf("%lu\n", ft_strlcat(dst, src, 15));
// 	printf("%s\n", dst);
// }
