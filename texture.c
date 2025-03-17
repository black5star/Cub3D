#include "cub.h"

void	detect_direction(t_game *game, int x, int y, double ray)
{
	if ((ray < PI / 2 || ray >= 2 * PI) && wall_checker(game, x, y + 1))
		game->flag = 'E';
	if ((ray <= PI / 2 || ray > 2 * PI) && wall_checker(game, x - 1, y))
		game->flag = 'S';
	if ((ray <= PI && ray > PI / 2) && (wall_checker(game, x, y + 1)
			|| !wall_checker(game, x + 1, y)))
		game->flag = 'W';
	if ((ray < PI && ray >= PI / 2) && wall_checker(game, x + 1, y))
		game->flag = 'S';
	if ((ray > PI && ray <= 3 * PI / 2) && wall_checker(game, x, y - 1))
		game->flag = 'W';
	if ((ray > PI && ray <= 3 * PI / 2) && wall_checker(game, x + 1, y))
		game->flag = 'N';
	if ((ray > (3 * PI / 2) || ray <= 0) && wall_checker(game, x, y - 1))
		game->flag = 'E';
	if ((ray >= (3 * PI / 2) || ray < 0) && wall_checker(game, x - 1, y)
		&& game->flag != 'S')
		game->flag = 'N';
}

unsigned int	get_wall_color(t_game *game, int x, int y)
{
	if (game->flag == 'N')
		return (get_pixel_img(game->wall_n, x, y));
	if (game->flag == 'S')
		return (get_pixel_img(game->wall_s, x, y));
	if (game->flag == 'W')
		return (get_pixel_img(game->wall_w, x, y));
	if (game->flag == 'E')
		return (get_pixel_img(game->wall_e, x, y));
	return (0);
}

void	draw_textures(t_game *game, int x, double y, double wall_h)
{
	int				i;
	double			h;
	double			step;
	unsigned int	color;

	i = -1;
	game->pos = fmod(game->pos, TILE_SIZE);
	step = TILE_SIZE / wall_h;
	h = round((WIND_H / 2) - (wall_h / 2));
	while (++i < h)
		my_put_pixel(game->image, x, i, game->c_color);
	while (h <= round((WIND_H / 2) + (wall_h / 2)))
	{
		color = get_wall_color(game, game->pos, round(y));
		my_put_pixel(game->image, x, h, color);
		y += step;
		h++;
	}
	h--;
	while (h++ < WIND_H)
		my_put_pixel(game->image, x, h, game->f_color);
}

void	vertical_line(t_game *game, int x, double dist)
{
	double	wall_h;

	if (dist <= 0)
		wall_h = (WIND_H * WALL_H) / 0.02;
	else
		wall_h = (WIND_H * WALL_H) / (dist);
	draw_textures(game, x, 0, wall_h);
}
