/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 08:57:38 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/05 08:57:38 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	mm_player_mark(t_img *map, t_player *p, int i)
{
	int	n;
	int	x;
	int	y;

	n = -1;
	x = p->pos_scaled->x;
	y = p->pos_scaled->y;
	while (n++ < i)
	{
		pixel_put(map, x - n, y - n, C_GREEN);
		pixel_put(map, x - n, y + n, C_GREEN);
		pixel_put(map, x - n, y, C_GREEN);
		pixel_put(map, x, y, C_GREEN);
		pixel_put(map, x, y + n, C_GREEN);
		pixel_put(map, x, y - n, C_GREEN);
		pixel_put(map, x + n, y + n, C_GREEN);
		pixel_put(map, x + n, y - n, C_GREEN);
		pixel_put(map, x + n, y, C_GREEN);
	}
}

static t_bool	check_valid_tile(t_data *cub3d, int key)
{
	if (key == KEY_D)
		if (cub3d->map->grid[cub3d->player->pos->y]
			[cub3d->player->pos->x + 1].type == WALL)
			return (FALSE);
	if (key == KEY_A)
		if (cub3d->map->grid[cub3d->player->pos->y]
			[cub3d->player->pos->x - 1].type == WALL)
			return (FALSE);
	if (key == KEY_W)
		if (cub3d->map->grid[cub3d->player->pos->y - 1]
			[cub3d->player->pos->x].type == WALL)
			return (FALSE);
	if (key == KEY_S)
		if (cub3d->map->grid[cub3d->player->pos->y + 1]
			[cub3d->player->pos->x].type == WALL)
			return (FALSE);
	return (TRUE);
}

void	rotate_player(t_data *cub3d, int key)
{
	if (key == KEY_Q)
	{
		if (cub3d->player->cardinal == NORTH)
			cub3d->player->cardinal = WEST;
		else if (cub3d->player->cardinal == SOUTH)
			cub3d->player->cardinal = EAST;
		else if (cub3d->player->cardinal == EAST)
			cub3d->player->cardinal = NORTH;
		else if (cub3d->player->cardinal == WEST)
			cub3d->player->cardinal = SOUTH;
	}
	if (key == KEY_E)
	{
		if (cub3d->player->cardinal == NORTH)
			cub3d->player->cardinal = EAST;
		else if (cub3d->player->cardinal == SOUTH)
			cub3d->player->cardinal = WEST;
		else if (cub3d->player->cardinal == EAST)
			cub3d->player->cardinal = SOUTH;
		else if (cub3d->player->cardinal == WEST)
			cub3d->player->cardinal = NORTH;
	}
}

void	render_player(t_data *cub3d)
{
	cub3d->player->pos_scaled->x = cub3d->player->pos->x
		* cub3d->minimap->scale.x;
	cub3d->player->pos_scaled->y = cub3d->player->pos->y
		* cub3d->minimap->scale.y;
	pixel_put(cub3d->minimap, cub3d->player->pos_scaled->x,
		cub3d->player->pos_scaled->y, C_GREEN);
	mm_player_mark(cub3d->minimap, cub3d->player, 5);
}

void	move_player(t_data *cub3d, int key)
{
	if (check_valid_tile(cub3d, key) && key == KEY_D)
		cub3d->player->pos->x += 1;
	if (check_valid_tile(cub3d, key) && key == KEY_A)
		cub3d->player->pos->x -= 1;
	if (check_valid_tile(cub3d, key) && key == KEY_W)
		cub3d->player->pos->y -= 1;
	if (check_valid_tile(cub3d, key) && key == KEY_S)
		cub3d->player->pos->y += 1;
	if (key == KEY_Q || key == KEY_E)
		rotate_player(cub3d, key);
}
