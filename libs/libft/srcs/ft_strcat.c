/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:59:34 by anayef            #+#    #+#             */
/*   Updated: 2023/11/27 20:05:11 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*str;

	if (dest == NULL || src == NULL)
		return (NULL);
	str = dest;
	while (*dest != '\0')
		dest++;
	ft_strcpy(dest, src);
	return (str);
}
