/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 08:49:26 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/15 10:13:42 by pbalbino         ###   ########.fr       */
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
	cub3d->player->pos_scaled_game = malloc(sizeof(t_coordinate));
	if (!cub3d->player->pos_scaled_game)
		ft_error(cub3d, MALLOC_ERR);
	cub3d->player->pos_scaled->x = -1;
	cub3d->player->pos_scaled->y = -1;
	//cub3d->player->pos_scaled_game->x = -1;
	//cub3d->player->pos_scaled_game->y = -1;
	cub3d->player->cardinal = -1;
	cub3d->player->set = -1;
}

static void	init_map(t_data *cub3d)
{
	int		i;

	i = -1;
	cub3d->map = malloc(sizeof(t_map));
	if (!cub3d->map)
		ft_error(NULL, MALLOC_ERR);
	cub3d->map->x_max = -1;
	cub3d->map->rows = -1;
	cub3d->map->grid = NULL;
	cub3d->map->textures = malloc(sizeof(t_texture *) * 4);
	if (!cub3d->map->textures)
		ft_error(NULL, MALLOC_ERR);
	while (++i < 4)
	{
		if (i < 3)
		{
			cub3d->map->floor[i] = -1;
			cub3d->map->ceiling[i] = -1;
		}
		cub3d->map->textures[i] = malloc(sizeof(t_texture));
		cub3d->map->textures[i]->path = NULL;
		cub3d->map->textures[i]->cardinal = i;
	}
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
	j--;
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
		if (map_start(line))
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
	init_map(cub3d);
	init_player(cub3d);
	while (++i < 4)
		if (!read_textures(cub3d, filename, i))
			ft_error(cub3d, MAP_ERR);
	if (!set_floor_ceiling(cub3d, filename))
		ft_error(cub3d, MAP_ERR);
	fetch_grid(cub3d, filename);
	if (cub3d->map->rows < 3)
		ft_error(cub3d, MAP_ERR);
	if (!load_grid(cub3d, filename))
		ft_error(cub3d, MAP_ERR);
	if (!is_closed(cub3d, cub3d->player->pos->x, cub3d->player->pos->y))
		ft_error(cub3d, MAP_ERR);
	if (!check_assets(cub3d))
		ft_error(cub3d, MAP_ERR);

}
