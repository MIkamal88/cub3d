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

static t_bool	check_valid_tile(t_data *cub3d, int key)
{
	if (key == KEY_RIGHT)
		if (cub3d->map->grid[cub3d->player->pos->y]
			[cub3d->player->pos->x + 1].type == WALL)
			return (FALSE);
	if (key == KEY_LEFT)
		if (cub3d->map->grid[cub3d->player->pos->y]
			[cub3d->player->pos->x - 1].type == WALL)
			return (FALSE);
	if (key == KEY_UP)
		if (cub3d->map->grid[cub3d->player->pos->y - 1]
			[cub3d->player->pos->x].type == WALL)
			return (FALSE);
	if (key == KEY_DOWN)
		if (cub3d->map->grid[cub3d->player->pos->y + 1]
			[cub3d->player->pos->x].type == WALL)
			return (FALSE);
	return (TRUE);
}

void	move_player(t_data *cub3d, int key)
{
	printf("player pos: %d, %d\n", cub3d->player->pos->x, cub3d->player->pos->y);
	if (key == KEY_RIGHT && check_valid_tile(cub3d, key))
		cub3d->player->pos->x += 1;
	if (key == KEY_LEFT && check_valid_tile(cub3d, key))
		cub3d->player->pos->x -= 1;
	if (key == KEY_UP && check_valid_tile(cub3d, key))
		cub3d->player->pos->y -= 1;
	if (key == KEY_DOWN && check_valid_tile(cub3d, key))
		cub3d->player->pos->y += 1;
}
