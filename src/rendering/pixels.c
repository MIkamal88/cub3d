/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:25:09 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/21 11:59:47 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (y >= img->h || x >= img->w || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	pixel_get(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

int	get_texture_color(t_img *texture, int x, int y)
{
	char	*pixel_color;
	int		color;

	pixel_color = texture->addr
		+ (y * texture->line_length + x * (texture->bpp / 8));
	color = *(unsigned int *)pixel_color;
	return (color);
}

int	create_trgb(int r, int g, int b)
{
	int	colour;

	colour = r;
	colour = 256 * colour + g;
	colour = 256 * colour + b;
	return (colour);
}
