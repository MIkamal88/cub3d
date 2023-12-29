/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_ft_memchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshehata <mshehata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 08:58:08 by mshehata          #+#    #+#             */
/*   Updated: 2022/11/10 08:58:09 by mshehata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*char_s;

	char_s = (char *) s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)c == (unsigned char)char_s[i])
			return ((char *)s + i);
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	char data[] = {'q', 'w', 'a', 's', 'r', 'p', 'z', 'x'};
// 	char *pos = ft_memchr(data, 'p', 8);
// 	if (pos == NULL)
// 		printf("NULL\n");
// 	else
// 		printf("pos[0] = %c\n", pos[1]);
// }
