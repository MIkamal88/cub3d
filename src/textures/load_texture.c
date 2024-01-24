/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:21:21 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/21 18:35:09 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	clean_texture_path(char *path)
{
	int	i;

	i = 0;
	while (path[i] != 0x0)
	{
		if (path[i] == '\n')
			path[i] = 0x0;
		i++;
	}
}

t_bool	load_texture(t_data *cube, int cardinal)
{
	t_img	*texture;

	texture = malloc(sizeof(t_img));
	clean_texture_path(cube->map->textures[cardinal]->path);
	texture->w = TILE_SIZE;
	texture->h = TILE_SIZE;
	texture->img_ptr = mlx_xpm_file_to_image(cube->win->mlx, \
	cube->map->textures[cardinal]->path, &texture->w, &texture->h);
	if (texture->img_ptr == NULL)
	{
		write_err("Error\nError while loading texture\n");
		return (FALSE);
	}
	texture->addr = mlx_get_data_addr(texture->img_ptr, &texture->bpp, \
	&texture->line_length, &texture->endian);
	cube->map->textures[cardinal]->texture_img = texture;
	return (TRUE);
}
