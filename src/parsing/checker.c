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
		if (!cub3d->map->textures[i]->is_set)
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

// t_bool	check_first_last_borders(t_data *cub3d)
// {
// 	int	i;
//
// 	i = 0;
// 	while (i <= cub3d->map->grid[0]->local_x_max)
// 	{
// 		if (cub3d->map->grid[0][i].type == WALL)
// 			i++;
// 		else if (cub3d->map->grid[0][i].type != EMPTY)
// 			return (FALSE);
// 		i++;
// 	}
// 	i = 0;
// 	while (i <= cub3d->map->grid[cub3d->map->rows - 1]->local_x_max)
// 	{
// 		if (cub3d->map->grid[cub3d->map->rows - 1][i].type == WALL)
// 			i++;
// 		else if (cub3d->map->grid[cub3d->map->rows - 1][i].type != EMPTY)
// 			return (FALSE);
// 		i++;
// 	}
// 	return (TRUE);
// }
//
// t_bool	check_right_left_borders(t_data *cub3d)
// {
// 	int	i;
// 	int	j;
//
// 	i = 0;
// 	while (++i < cub3d->map->rows - 1)
// 	{
// 		j = 0;
// 		while (j <= cub3d->map->grid[i]->local_x_max)
// 		{
// 			if (cub3d->map->grid[i][j].type == WALL)
// 				j++;
// 			else if (cub3d->map->grid[i][j].type != EMPTY)
// 				return (FALSE);
// 			j++;
// 		}
// 	}
// 	return (TRUE);
// }
