/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:13:44 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/31 16:13:44 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Allocate memory for the map grid by counting the number of lines of the map
// Then allocate memory for each line by counting the number of characters
// Assigning whether each point on your grid is a wall or not,
// a player or not, or NULL(space)

t_bool		set_grid(int fd, char *line);
static int	get_height(int fd, char *line);

t_bool	fetch_grid(t_data *cub3d, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line || fd < 0)
		ft_error(cub3d, MAP_ERR);
	while (line)
	{
		if (ft_strnstr(line, "1", 4))
		{
			if (set_grid(fd, line))
				break ;
		}
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (TRUE);
}

t_bool	set_grid(int fd, char *line)
{
	int		y;

	y = get_height(fd, line);
	printf("y: %d\n", y);
	return (TRUE);
}

static int	get_height(int fd, char *line)
{
	int		i;

	i = 0;
	while (line)
	{
		printf("line: %s", line);
		if (line)
			free(line);
		line = get_next_line(fd);
		i++;
	}
	return (i);
}
