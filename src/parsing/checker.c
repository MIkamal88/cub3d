/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:15:07 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/15 10:13:33 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*validate_texture(t_data *cub3d, char *filename, char *direction);
static char	*search_for_asset(char *line, char *direction);

t_bool	read_textures(t_data *cub3d, char *filename, int cardinal)
{
	if (cardinal == 0)
		cub3d->map->textures[cardinal]->path = validate_texture
			(cub3d, filename, "NO");
	else if (cardinal == 1)
		cub3d->map->textures[cardinal]->path = validate_texture
			(cub3d, filename, "SO");
	else if (cardinal == 2)
		cub3d->map->textures[cardinal]->path = validate_texture
			(cub3d, filename, "EA");
	else if (cardinal == 3)
		cub3d->map->textures[cardinal]->path = validate_texture
			(cub3d, filename, "WE");
	else
		return (FALSE);
	return (TRUE);
}

static char	*validate_texture(t_data *cub3d, char *filename, char *direction)
{
	int		fd;
	char	*line;
	char	*texture;

	texture = NULL;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line || fd < 0)
		ft_error(cub3d, MAP_ERR);
	while (line)
	{
		texture = search_for_asset(line, direction);
		if (texture)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	clear_read(line, fd);
	if (!texture)
		ft_error(cub3d, MAP_ERR);
	return (texture);
}

static char	*search_for_asset(char *line, char *direction)
{
	int		i;
	char	**split;
	char	*path;

	i = -1;
	path = NULL;
	split = ft_split(line, ' ');
	while (split[++i])
	{
		if (ft_strncmp(split[i], direction, ft_strlen(direction)) == 0)
		{
			if (!split[i + 1])
				free_double_ptr((void **)split);
			else
			{
				if (valid_extension(split[i + 1], ".xpm"))
					path = ft_strdup(split[i + 1]);
				free_double_ptr((void **)split);
				return (path);
			}
		}
	}
	if (split)
		free_double_ptr((void **)split);
	return (NULL);
}

t_bool	check_assets(t_data *cub3d)
{
	int	i;

	i = -1;
	cub3d->player->pos_game->x = (cub3d->player->pos->x * TILE_SIZE)
		+ TILE_SIZE / 2;
	cub3d->player->pos_game->y = (cub3d->player->pos->y * TILE_SIZE)
		+ TILE_SIZE / 2;
	if (cub3d->player->cardinal == 'N')
		cub3d->player->cardinal = 0;
	else if (cub3d->player->cardinal == 'S')
		cub3d->player->cardinal = 1;
	else if (cub3d->player->cardinal == 'E')
		cub3d->player->cardinal = 2;
	else if (cub3d->player->cardinal == 'W')
		cub3d->player->cardinal = 3;
	while (++i < 4)
		if (!cub3d->map->textures[i]->path)
			return (FALSE);
	i = -1;
	while (++i < 3)
		if (cub3d->map->floor[i] < 0 || cub3d->map->ceiling[i] < 0)
			return (FALSE);
	return (TRUE);
}

t_bool	is_closed(t_data *cub3d, int x, int y)
{
	if (x < 0 || y < 0 || y >= cub3d->map->rows
		|| x >= cub3d->map->grid[y]->local_x_max \
		|| cub3d->map->grid[y][x].type == EMPTY)
		return (FALSE);
	if (cub3d->map->grid[y][x].type == WALL)
		return (TRUE);
	if (cub3d->map->grid[y][x].visited == TRUE)
		return (TRUE);
	if (cub3d->map->grid[y][x].type == HALL && \
		cub3d->map->grid[y][x].visited == TRUE)
		return (TRUE);
	cub3d->map->grid[y][x].visited = TRUE;
	if (!is_closed(cub3d, x + 1, y) || !is_closed(cub3d, x - 1, y)
		|| !is_closed(cub3d, x, y + 1) || !is_closed(cub3d, x, y - 1))
		return (FALSE);
	return (TRUE);
}
