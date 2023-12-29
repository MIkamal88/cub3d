/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 08:02:59 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/05 08:02:59 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	join_args(int argn, va_list argl, char **result)
{
	char	*buf;
	char	*tmp;
	int		i;

	i = -1;
	while (++i < argn)
	{
		buf = va_arg(argl, char *);
		if (i == 0)
			*result = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(*result, buf);
			if (*result)
				free(*result);
			*result = tmp;
		}
	}
}

char	*ft_strnjoin(int argn, ...)
{
	char	*result;
	va_list	argl;

	if (argn == 0)
		return (NULL);
	va_start(argl, argn);
	result = NULL;
	join_args(argn, argl, &result);
	va_end(argl);
	return (result);
}
