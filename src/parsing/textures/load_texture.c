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

#include "../../../include/cub3d.h"

void	init_textures(t_data *cub3d, int cardinal)
{
	cub3d->map->textures[cardinal] = malloc(sizeof(t_texture));
	if (!cub3d->map->textures[cardinal])
		ft_error(cub3d, MALLOC_ERR);
	cub3d->map->textures[cardinal]->is_set = FALSE;
	cub3d->map->textures[cardinal]->path = malloc(sizeof(t_path));
	cub3d->map->textures[cardinal]->path->cardinal = -1;
	cub3d->map->textures[cardinal]->path->xpm_file = NULL;
	cub3d->map->textures[cardinal]->texture_img = NULL;
}

t_bool	load_texture(t_data *cube, int cardinal)
{
	int		i;
	char	*path;
	t_img	*texture;

	i = -1;
	path = cube->map->textures[cardinal]->path->xpm_file;
	while (path[++i] != 0x0)
		if (path[i] == '\n')
			path[i] = 0x0;
	texture = malloc(sizeof(t_img));
	if (!texture)
		ft_error(cube, MAP_ERR);
	texture->w = TILE_SIZE;
	texture->h = TILE_SIZE;
	texture->img_ptr = mlx_xpm_file_to_image(cube->win->mlx, \
	cube->map->textures[cardinal]->path->xpm_file, &texture->w, &texture->h);
	if (texture->img_ptr == NULL)
		ft_error(cube, MAP_ERR);
	texture->addr = mlx_get_data_addr(texture->img_ptr, &texture->bpp, \
	&texture->line_length, &texture->endian);
	cube->map->textures[cardinal]->texture_img = texture;
	return (TRUE);
}

t_bool	read_load_texture(t_data *cub3d, char *filename)
{
	int	cardinal;

	cardinal = -1;
	if (read_textures(cub3d, filename) == TRUE)
	{
		while (++cardinal < 4)
		{
			if (cub3d->map->textures[cardinal]->is_set == TRUE)
				if (!load_texture(cub3d, cardinal))
					return (FALSE);
		}
	}
	return (TRUE);
}
