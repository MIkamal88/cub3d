/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 08:49:26 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/30 08:49:26 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player(t_data *cub3d)
{
	cub3d->player = malloc(sizeof(t_player));
	if (!cub3d->player)
		ft_error(cub3d, MALLOC_ERR);
	cub3d->player->pos = malloc(sizeof(t_point));
	if (!cub3d->player->pos)
		ft_error(cub3d, MALLOC_ERR);
	cub3d->player->pos_scaled = malloc(sizeof(t_point));
	if (!cub3d->player->pos_scaled)
		ft_error(cub3d, MALLOC_ERR);
	cub3d->player->pos_scaled->x = -1;
	cub3d->player->pos_scaled->y = -1;
	cub3d->player->pos->x = -1;
	cub3d->player->pos->y = -1;
	cub3d->player->pos->type = -1;
	cub3d->player->cardinal = -1;
	cub3d->player->set = -1;
}

static t_map	*init_map(void)
{
	int		i;
	t_map	*map;

	i = -1;
	map = malloc(sizeof(t_map));
	if (!map)
		ft_error(NULL, MALLOC_ERR);
	map->x_max = -1;
	map->rows = -1;
	map->grid = NULL;
	map->textures = malloc(sizeof(t_texture *) * 4);
	if (!map->textures)
		ft_error(NULL, MALLOC_ERR);
	while (++i < 4)
	{
		if (i < 3)
		{
			map->floor[i] = -1;
			map->ceiling[i] = -1;
		}
		map->textures[i] = malloc(sizeof(t_texture));
		map->textures[i]->path = NULL;
		map->textures[i]->cardinal = i;
	}
	return (map);
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

static t_bool	fetch_grid(t_data *cub3d, char *filename)
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

void	map_read(t_data *cub3d, char *filename)
{
	int		i;

	i = -1;
	cub3d->map = init_map();
	init_player(cub3d);
	while (++i < 4)
		if (!read_textures(cub3d, filename, i))
			ft_error(cub3d, MAP_ERR);
	if (!set_floor_ceiling(cub3d, filename))
		ft_error(cub3d, MAP_ERR);
	fetch_grid(cub3d, filename);
	if (cub3d->map->rows <= 3)
		ft_error(cub3d, MAP_ERR);
	if (!load_grid(cub3d, filename))
		ft_error(cub3d, MAP_ERR);
	if (cub3d->player->cardinal == 'N')
		cub3d->player->cardinal = 0;
	else if (cub3d->player->cardinal == 'S')
		cub3d->player->cardinal = 1;
	else if (cub3d->player->cardinal == 'E')
		cub3d->player->cardinal = 2;
	else if (cub3d->player->cardinal == 'W')
		cub3d->player->cardinal = 3;
}
