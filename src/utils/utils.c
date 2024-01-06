/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:51:24 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/30 15:51:24 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	clear_read(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

t_bool	valid_extension(char *file, char *ext)
{
	char	*extension;

	if (!file || !ext)
		return (FALSE);
	extension = ft_strrchr(file, '.');
	if (!extension)
		return (FALSE);
	else if (ft_strncmp(extension, ext, ft_strlen(ext)))
		return (FALSE);
	else
		return (TRUE);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

void	swap_points(t_point *p0, t_point *p1)
{
	int	tmp;
	int	tmp2;

	tmp = p0->x;
	p0->x = p1->x;
	p1->x = tmp;
	tmp2 = p0->y;
	p0->y = p1->y;
	p1->y = tmp2;
}

t_bool	map_start(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
			return (FALSE);
		i++;
	}
	if (ft_strnstr(line, "111", ft_strlen(line)))
		return (TRUE);
	return (FALSE);
}
