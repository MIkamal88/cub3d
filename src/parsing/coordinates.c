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

static t_bool		read_grid(t_data *cub3d, int fd, char *line);
static t_bool		set_grid(t_data *cub3d, char *line, int j);

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
		if (ft_strnstr(line, "1111", ft_strlen(line)))
		{
			if (read_grid(cub3d, fd, line))
				break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (TRUE);
}

static t_bool	read_grid(t_data *cub3d, int fd, char *line)
{
	int	j;

	j = 0;
	while (line)
	{
		cub3d->map->grid[j] = ft_calloc(sizeof(t_point *), ft_strlen(line));
		set_grid(cub3d, line, j);
		if (line)
			free(line);
		line = get_next_line(fd);
		j++;
	}
	cub3d->map->rows = j;
	if (cub3d->map->rows <= 0)
		return (FALSE);
	return (TRUE);
}

static t_bool	set_grid(t_data *cub3d, char *line, int j)
{
	int	i;

	i = 0;
	while (line[i])
	{
		cub3d->map->grid[j][i].y = j;
		cub3d->map->grid[j][i].x = i;
		if (line[i] == '1')
			cub3d->map->grid[j][i].type = WALL;
		else if (line[i] == ' ')
			cub3d->map->grid[j][i].type = EMPTY;
		else if (ft_strchr("NSWE", line[i]))
		{
			cub3d->map->grid[j][i].type = PLAYER;
			cub3d->player->pos->x = i;
			cub3d->player->pos->y = j;
			cub3d->player->cardinal = line[i];
		}
		else
			cub3d->map->grid[j][i].type = HALL;
		i++;
	}
	return (TRUE);
}
