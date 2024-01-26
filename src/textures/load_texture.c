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

void	init_textures(t_data *cub3d, int cardinal)
{
	cub3d->map->textures[cardinal] = malloc(sizeof(t_texture));
	if (!cub3d->map->textures[cardinal])
		ft_error(cub3d, MALLOC_ERR);
	cub3d->map->textures[cardinal]->is_set = FALSE;
	cub3d->map->textures[cardinal]->cardinal = cardinal;
	cub3d->map->textures[cardinal]->path = NULL;
	cub3d->map->textures[cardinal]->texture_img = NULL;
}

t_bool	read_textures(t_data *cub3d, char *filename, int cardinal)
{
	if (cardinal == 0)
		cub3d->map->textures[cardinal]->path = validate_texture
			(cub3d, filename, "NO");
	else if (cardinal == 1)
		cub3d->map->textures[cardinal]->path = validate_texture
			(cub3d, filename, "SO");
	else if (cardinal == 2)
		cub3d->map->textures[cardinal]->path = validate_texture
			(cub3d, filename, "EA");
	else if (cardinal == 3)
		cub3d->map->textures[cardinal]->path = validate_texture
			(cub3d, filename, "WE");
	else
		return (FALSE);
	return (TRUE);
}

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
	if (!texture)
		return (FALSE);
	clean_texture_path(cube->map->textures[cardinal]->path);
	texture->w = TILE_SIZE;
	texture->h = TILE_SIZE;
	texture->img_ptr = mlx_xpm_file_to_image(cube->win->mlx, \
	cube->map->textures[cardinal]->path, &texture->w, &texture->h);
	if (texture->img_ptr == NULL)
	{
		write_err("Error while loading texture\n");
		return (FALSE);
	}
	texture->addr = mlx_get_data_addr(texture->img_ptr, &texture->bpp, \
	&texture->line_length, &texture->endian);
	cube->map->textures[cardinal]->texture_img = texture;
	return (TRUE);
}

t_bool	read_load_texture(t_data *cub3d, char *filename)
{
	int	cardinal;

	cardinal = -1;
	while (++cardinal < 4)
		if (!read_textures(cub3d, filename, cardinal))
			return (FALSE);
	if (cardinal == 4)
	{
		cardinal = -1;
		while (++cardinal < 4)
		{
			if (cub3d->map->textures[cardinal]->is_set == FALSE)
			{
				if (!load_texture(cub3d, cardinal))
					return (FALSE);
			}
			cub3d->map->textures[cardinal]->is_set = TRUE;
		}
	}
	return (TRUE);
}
