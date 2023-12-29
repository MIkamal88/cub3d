/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshehata <mshehata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:11:18 by mshehata          #+#    #+#             */
/*   Updated: 2022/11/23 10:55:48 by mshehata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (c == 0)
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == ((char)c))
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*str;
// 	char	str2[] = "bonjour";

// 	if (!(str = ft_strrchr(str2, '\0')))
// 		printf("NULL");
// 	else
// 	{
// 		printf("%s", str);
// 		if (str != str2 + 7)
// 			printf("\nReturn value is false");
// 	}
// }
