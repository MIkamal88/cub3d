/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:15:07 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/30 09:15:07 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*validate_texture(t_data *cub3d, char *filename, char *direction);
static char	*search_for_asset(char *line, char *direction);

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

static char	*validate_texture(t_data *cub3d, char *filename, char *direction)
{
	int		fd;
	char	*line;
	char	*texture;

	texture = NULL;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line || fd < 0)
		ft_error(cub3d, MAP_ERR);
	while (line)
	{
		texture = search_for_asset(line, direction);
		if (texture)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	clear_read(line, fd);
	if (!texture)
		ft_error(cub3d, MAP_ERR);
	return (texture);
}

static char	*search_for_asset(char *line, char *direction)
{
	int		i;
	char	**split;
	char	*path;

	i = -1;
	path = NULL;
	split = ft_split(line, ' ');
	while (split[++i])
	{
		if (ft_strncmp(split[i], direction, ft_strlen(direction)) == 0)
		{
			if (!split[i + 1])
				free_double_ptr((void **)split);
			else
			{
				if (valid_extension(split[i + 1], ".xpm"))
					path = ft_strdup(split[i + 1]);
				free_double_ptr((void **)split);
				return (path);
			}
		}
	}
	if (split)
		free_double_ptr((void **)split);
	return (NULL);
}
