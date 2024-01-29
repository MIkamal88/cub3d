/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:03:43 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/29 10:03:43 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static int	decide_direction(t_data *cub3d, char *line_split)
{
	int	cardinal;

	if (ft_strncmp(line_split, "NO", ft_strlen(line_split)) == 0)
	{
		cub3d->map->textures[0]->path->cardinal = 0;
		cardinal = 1;
	}
	else if (ft_strncmp(line_split, "SO", ft_strlen(line_split)) == 0)
	{
		cub3d->map->textures[1]->path->cardinal = 1;
		cardinal = 2;
	}
	else if (ft_strncmp(line_split, "EA", ft_strlen(line_split)) == 0)
	{
		cub3d->map->textures[2]->path->cardinal = 2;
		cardinal = 3;
	}
	else if (ft_strncmp(line_split, "WE", ft_strlen(line_split)) == 0)
	{
		cub3d->map->textures[3]->path->cardinal = 3;
		cardinal = 4;
	}
	else
		cardinal = 0;
	return (cardinal);
}

static t_bool	search_for_asset(t_data *cub3d, char *line)
{
	char	**split;
	char	*path;
	int		cardinal;

	split = ft_split(line, ' ');
	cardinal = decide_direction(cub3d, split[0]);
	path = NULL;
	if (cardinal && cub3d->map->textures[cardinal -1]->is_set == TRUE)
	{
		free_double_ptr((void **)split);
		return (FALSE);
	}
	if (cardinal && cub3d->map->textures[cardinal -1]->is_set == FALSE)
		if (split[1] && !split[2])
			if (valid_extension(split[1], ".xpm"))
				path = ft_strdup(split[1]);
	if (split)
		free_double_ptr((void **)split);
	if (path)
	{
		cub3d->map->textures[cardinal -1]->is_set = TRUE;
		cub3d->map->textures[cardinal -1]->path->xpm_file = ft_strdup(path);
		free(path);
	}
	return (TRUE);
}

t_bool	read_textures(t_data *cub3d, char *filename)
{
	int		fd;
	int		i;
	char	*line;

	i = -1;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line || fd < 0)
		ft_error(cub3d, MAP_ERR);
	while (line)
	{
		if (!search_for_asset(cub3d, line))
		{
			clear_read(line, fd);
			return (FALSE);
		}
		free(line);
		line = get_next_line(fd);
	}
	clear_read(line, fd);
	while (++i < 4)
		if (!cub3d->map->textures[i]->is_set)
			return (FALSE);
	return (TRUE);
}
