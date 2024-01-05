/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:25:09 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/29 15:25:09 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (y >= img->h || x >= img->w || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	player_arrow(t_img *map, t_player *p, int i)
{
	if (p->cardinal == NORTH)
	{
		pixel_put(map, p->pos_scaled->x - i, p->pos_scaled->y + i, C_GREEN);
		pixel_put(map, p->pos_scaled->x + i, p->pos_scaled->y + i, C_GREEN);
	}
	if (p->cardinal == SOUTH)
	{
		pixel_put(map, p->pos_scaled->x - i, p->pos_scaled->y - i, C_GREEN);
		pixel_put(map, p->pos_scaled->x + i, p->pos_scaled->y - i, C_GREEN);
	}
	if (p->cardinal == EAST)
	{
		pixel_put(map, p->pos_scaled->x - i, p->pos_scaled->y - i, C_GREEN);
		pixel_put(map, p->pos_scaled->x - i, p->pos_scaled->y + i, C_GREEN);
	}
	if (p->cardinal == WEST)
	{
		pixel_put(map, p->pos_scaled->x + i, p->pos_scaled->y - i, C_GREEN);
		pixel_put(map, p->pos_scaled->x + i, p->pos_scaled->y + i, C_GREEN);
	}
}
