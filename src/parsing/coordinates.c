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

static t_bool		get_height(t_data *cub3d, int fd, char *line);
static t_bool		set_grid_row(t_data *cub3d, char *line, int j);
static t_bool		set_grid(t_data *cub3d, int fd, char *line, int *j);

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
			if (get_height(cub3d, fd, line))
				break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (TRUE);
}

static t_bool	get_height(t_data *cub3d, int fd, char *line)
{
	int	j;

	j = 0;
	while (line)
	{
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

t_bool	load_grid(t_data *cub3d, char *filename)
{
	int		fd;
	int		j;
	char	*line;

	fd = open(filename, O_RDONLY);
	cub3d->map->grid = ft_calloc(sizeof(t_point **), cub3d->map->rows);
	line = get_next_line(fd);
	if (!line || fd < 0)
		ft_error(cub3d, MAP_ERR);
	while (line)
	{
		if (ft_strnstr(line, "1111", ft_strlen(line)))
		{
			j = 0;
			if (set_grid(cub3d, fd, line, &j))
				break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (TRUE);
}

static t_bool	set_grid(t_data *cub3d, int fd, char *line, int *j)
{
	while (line)
	{
		cub3d->map->grid[*j] = ft_calloc(sizeof(t_point), ft_strlen(line));
		if (!set_grid_row(cub3d, line, *j))
			return (FALSE);
		(*j)++;
		free(line);
		line = get_next_line(fd);
	}
	if (cub3d->player->pos->type == -1 || cub3d->player->cardinal == -1)
		ft_error(cub3d, MAP_ERR);
	if (cub3d->player->cardinal == 'N')
		cub3d->player->cardinal = 0;
	else if (cub3d->player->cardinal == 'S')
		cub3d->player->cardinal = 1;
	else if (cub3d->player->cardinal == 'E')
		cub3d->player->cardinal = 2;
	else if (cub3d->player->cardinal == 'W')
		cub3d->player->cardinal = 3;
	return (TRUE);
}

static t_bool	set_grid_row(t_data *cub3d, char *line, int j)
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
			cub3d->player->pos->type = PLAYER;
			cub3d->player->pos->x = i;
			cub3d->player->pos->y = j;
			cub3d->player->cardinal = (int)line[i];
		}
		else if (line[i] == '0')
			cub3d->map->grid[j][i].type = HALL;
		i++;
	}
	return (TRUE);
}
