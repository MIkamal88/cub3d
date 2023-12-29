/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshehata <mshehata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:29:20 by mshehata          #+#    #+#             */
/*   Updated: 2023/01/31 11:03:30 by mshehata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * sign);
}

// int	main(void)
// {
// 	int		*x;
// 	int		i;
// 	char	*line;
// 	int		n;

// 	n = 0;
// 	i = 0;
// 	line = "1  0  0  1  0  0  2  0  0  3  0  0  4  0  0  5  0  0  6";
// 	while (line[i])
// 	{
// 		x[n] = ft_atoi(line);
// 		i++;
// 	}
// 	printf("%d", x[n]);
// }
