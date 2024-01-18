/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:13:44 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/15 10:13:37 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Allocate memory for the map grid by counting the number of lines of the map
// Then allocate memory for each line by counting the number of characters
// Assigning whether each point on your grid is a wall or not,
// a player or not, or NULL(space)

static t_bool		set_grid_row(t_data *cub3d, char *line, int j, int len);
static t_bool		set_grid(t_data *cub3d, int fd, char *line, int *j);

t_bool	load_grid(t_data *cub3d, char *filename)
{
	int		fd;
	int		j;
	char	*line;

	fd = open(filename, O_RDONLY);
	cub3d->map->grid = ft_calloc(sizeof(t_point *), cub3d->map->rows);
	line = get_next_line(fd);
	if (!line || fd < 0)
		ft_error(cub3d, MAP_ERR);
	while (line)
	{
		if (map_start(line))
		{
			j = 0;
			if (set_grid(cub3d, fd, line, &j))
				break ;
			else
				return (FALSE);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (TRUE);
}

static t_bool	set_grid(t_data *cub3d, int fd, char *line, int *j)
{
	int	len;

	while (line)
	{
		len = ft_strlen(line);
		if (len - 1 >= cub3d->map->x_max)
			cub3d->map->x_max = len - 1;
		cub3d->map->grid[*j] = ft_calloc(sizeof(t_point), len);
		if (!set_grid_row(cub3d, line, *j, len))
		{
			clear_read(line, fd);
			return (FALSE);
		}
		(*j)++;
		free(line);
		line = get_next_line(fd);
	}
	return (TRUE);
}

static void	assign_point(t_data *cub3d, int i, int j, int len)
{
	cub3d->map->grid[j][i].x = i;
	cub3d->map->grid[j][i].y = j;
	cub3d->map->grid[j][i].local_x_max = len;
	cub3d->map->grid[j][i].visited = FALSE;
}

static t_bool	set_grid_row(t_data *cub3d, char *line, int j, int len)
{
	int	i;

	i = -1;
	while (line[++i] && line[i] != '\n')
	{
		if (line[i] == '1')
			cub3d->map->grid[j][i].type = WALL;
		else if (line[i] == ' ')
			cub3d->map->grid[j][i].type = EMPTY;
		else if (ft_strchr("NSWE", line[i]) && (cub3d->player->set != TRUE))
		{
			cub3d->map->grid[j][i].type = PLAYER;
			cub3d->player->set = TRUE;
			cub3d->player->pos->type = PLAYER;
			cub3d->player->pos_scaled_game->x = (i * TILE_SIZE) + TILE_SIZE / 2;
			cub3d->player->pos_scaled_game->y = (j * TILE_SIZE) + TILE_SIZE / 2;
			cub3d->player->cardinal = (int)line[i];
		}
		else if (line[i] == '0')
			cub3d->map->grid[j][i].type = HALL;
		else
			return (FALSE);
		assign_point(cub3d, i, j, len);
	}
	return (TRUE);
}
