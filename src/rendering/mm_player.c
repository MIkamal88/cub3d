/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 08:57:38 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/16 21:54:21 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"








void	get_current_rotation_angle(t_data *cub3d)
{
	if (cub3d->player->cardinal == NORTH)
		cub3d->player->rotation_angle = 271 * (M_PI / 180);
	else if (cub3d->player->cardinal ==  SOUTH)
		cub3d->player->rotation_angle = 91 * (M_PI / 180);
	else if (cub3d->player->cardinal ==  EAST)
		cub3d->player->rotation_angle = 1 * (M_PI / 180);
	else if (cub3d->player->cardinal ==  WEST)
		cub3d->player->rotation_angle = 181 * (M_PI / 180);
}


void	rotate_player(t_data *cub3d, int key)
{
	if (key == KEY_LEFT)
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
	if (key == KEY_RIGHT)
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
	get_current_rotation_angle(cub3d);
}

void	render_player(t_data *cub3d)
{
	(void)cub3d;
//	int	i;

//	i = -1;
//	cub3d->player->pos_scaled->x = cub3d->player->pos->x
//		* cub3d->minimap->scale.x;
//	cub3d->player->pos_scaled->y = cub3d->player->pos->y
//		* cub3d->minimap->scale.y;
//	pixel_put(cub3d->minimap, cub3d->player->pos_scaled->x,
//		cub3d->player->pos_scaled->y, C_GREEN);
//	while (++i < 5)
//		mm_player_mark(cub3d->minimap, cub3d->player, i);
}

