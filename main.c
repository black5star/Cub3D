#include "cub.h"

double dgr_to_rad(double degrees) 
{
    return (degrees * (PI / 180.0));
}

int	ft_exit(t_game *game)
{
	ft_free(game);
	exit(0);
}
int	wall_checker(t_game *game, int x, int y)
{
	int	i;
	int	j;

	if (x <= 0 || y <= 0)
		return (1);
	i = x / TILE_SIZE;
	j = y / TILE_SIZE;
	if (game->map[j] && game->map[j][i])
	{
		if (game->map[j][i] == '1')
			return (1);
	}
	return (0);
}
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
	if ((ray >= (3 * PI / 2) || ray < 0) && wall_checker(game, x - 1, y))
		game->flag = 'N';
}
double	dist_calc(t_game *game, double x, double y, double ray)
{
	double dx;
    double dy;
    double dist;

    dx = fabs(x - game->px);
    dy = fabs(y - game->py);
    dist = sqrt(dx * dx + dy * dy);
    dist *= cos(ray - game->pa);
    return (dist);
}

double	dda_line_drawing(t_game *game, double x, double y, double ray)
{
	double x_inc;
	double y_inc;
	double dx;
	double dy;
	double step;

	dx = cos(ray);
	dy = sin(ray);
	if (fabs(dx) > fabs(dy))
        step = fabs(dx);
	else
        step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	while (x >= 0 && x <= WIND_W && y >= 0 && y <= WIND_H)
	{
		if (wall_checker(game, round(x), round(y)))
		{
			detect_direction(game, round(x), round(y), ray);
			if (game->flag == 'E' || game->flag == 'W')
				game->pos =  y;
			if (game->flag == 'S' || game->flag == 'N')
				game->pos =  x;
			dx = dist_calc(game, x, y, ray);
			break;
		}
		// my_put_pixel(game->image, round(x), round(y), GREEN);
		x += x_inc;
		y += y_inc;
	}
	return (dx);
}

int can_move(t_game *game, int x, int y)
{
	int i;
	int j;

	j = y;
	while(j <= (y + (TILE_SIZE / 2)))
	{
		i = x;
		while(i <= (x + (TILE_SIZE / 2)))
		{
			if (wall_checker(game, i, j))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}
unsigned int get_wall_color(t_game *game, int x, int y)
{
	if(game->flag == 'N')
		return (get_pixel_img(game->wall_n, x, y));
	if(game->flag == 'S')
		return (get_pixel_img(game->wall_s, x, y));
	if(game->flag == 'W')
		return (get_pixel_img(game->wall_w, x, y));
	if(game->flag == 'E')
		return (get_pixel_img(game->wall_e, x, y));
	return(0);
}
void	draw_textures(t_game *game, int x, double y, double wall_h)
{
	double	step;
	double	h;
	unsigned int color;
	
	game->pos = fmod(game->pos, TILE_SIZE);
	step = TILE_SIZE / wall_h;
	h = round((WIND_H / 2) - (wall_h / 2));
	while (h <= round((WIND_H / 2) + (wall_h / 2)))
	{
		color = get_wall_color(game, game->pos, round(y));
		my_put_pixel(game->image, x, h, color);
		y += step;
		h++;
	}
}
void	vertical_line(t_game *game, int x, double dist)
{
	double wall_h;

	if(!dist)
		wall_h = WIND_H;
	else
		wall_h = (WIND_H * WALL_H) / (dist);
	draw_textures(game, x, 0, wall_h);
}
void	ray_cast(t_game *game, int x, int y, double ray)
{
	double	dist;
	double	i;
	double	angle;

	i = 0;
	angle = ray - (dgr_to_rad(FOV / 2));
	while (i <= 1280)
	{
		dist = dda_line_drawing(game, x, y, angle);
		vertical_line(game, i, dist);
		i++;;
		angle += dgr_to_rad(ANG_STEP);
	}
}

void	render_map(t_game *game)
{
	int i;
	int j = -1;

	while(game->map && game->map[++j])
	{
		i = -1;
		while(game->map[j][++i])
		{
			// if(game->map[j][i] == '1')
			// 	draw_square(game->image, i * TILE_SIZE, j * TILE_SIZE, RED);
			// else
			// 	draw_square(game->image, i * TILE_SIZE, j * TILE_SIZE, WHITE);
			if (game->map[j][i] == game->pv)
				game->map[j][i] = '0';
		}
	}
	// draw_player(game->image, game->px, game->py, BLACK);
}

void	go_up(t_game *game)
{
	double	x;
	double	y;

	x = round(cos(game->pa) * SPEED);
	y = round(sin(game->pa) * SPEED);
	if (!can_move(game, game->px + x, game->py + y))
	{
		game->px += x;
		game->py += y;
	}
}

void	go_down(t_game *game)
{
	double	x;
	double	y;

	x = round(cos(game->pa) * SPEED);
	y = round(sin(game->pa) * SPEED);
	if (!can_move(game, game->px - x, game->py - y))
	{
		game->px -= x;
		game->py -= y;
	}
}

void	to_right(t_game *game)
{
	double	x;
	double	y;

	x = round(sin(game->pa) * SPEED);
	y = round(cos(game->pa) * SPEED);
	if (game->key[100] && !can_move(game, game->px - x, game->py + y))
	{
		game->px -= x;
		game->py += y;
	}
}

void	to_left(t_game *game)
{
	double	x;
	double	y;

	x = round(sin(game->pa) * SPEED);
	y = round(cos(game->pa) * SPEED);
	if (!can_move(game, game->px + x, game->py - y))
	{
		game->px += x;
		game->py -= y;
	}
}

void	turn_left(t_game *game)
{
	game->pa -= dgr_to_rad(ANG_STEP + SPEED);
	if (game->pa <= 0)
		game->pa += (2 * PI);
}

void	turn_right(t_game *game)
{
	game->pa += dgr_to_rad(ANG_STEP + SPEED);
	if (game->pa >= (2 * PI))
		game->pa -= (2 * PI);
}

void	ft_key_hook(t_game *game)
{
	if (game->key[131])
		turn_left(game);
	if (game->key[130])
		turn_right(game);
	if (game->key[119])
		go_up(game);
	if (game->key[115])
		go_down(game);
	if (game->key[100])
		to_right(game);
	if (game->key[97])
		to_left(game);
}
int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit(ft_exit(game));
	if (keycode == 65363)
		game->key[130] = 1;
	if (keycode == 65361)
		game->key[131] = 1;
	if (keycode <= 127)
		game->key[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 65363)
		game->key[130] = 0;
	if (keycode == 65361)
		game->key[131] = 0;
	if (keycode <= 127)
		game->key[keycode] = 0;
	return (0);
}
int	render_3d(t_game *game)
{
	ft_key_hook(game);
	mlx_destroy_image(game->mlx, game->image.img_ptr);
	game->image = create_img(game, WIND_W, WIND_H);
	fill_map(game->image, CEILLING, BLACK);
	ray_cast(game, game->px + (TILE_SIZE / 4), game->py + (TILE_SIZE / 4), game->pa);
	render_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img_ptr, 0, 0);
	return (0);
}
void	init_image(t_game *game)
{
	if (game->pv == 'S')
		game->pa = (PI / 2);
	else if (game->pv == 'N')
		game->pa = (3 * PI) / 2;
	else if (game->pv == 'E')
		game->pa = 0;
	else if (game->pv == 'W')
		game->pa = PI;
	game->key = ft_calloc(150, sizeof(char *));
	game->image = create_img(game, WIND_W, WIND_H);
	game->wall_e = create_img(game, TILE_SIZE, TILE_SIZE);
	game->wall_n = create_img(game, TILE_SIZE, TILE_SIZE);
	game->wall_s = create_img(game, TILE_SIZE, TILE_SIZE);
	game->wall_w = create_img(game, TILE_SIZE, TILE_SIZE);
	game->wall_e = new_file_img(game->east, game);
	game->wall_n = new_file_img(game->north, game);
	game->wall_s = new_file_img(game->south, game);
	game->wall_w = new_file_img(game->west, game);
	render_3d(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img_ptr, 0, 0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (1);
	game = parsing(av[1]);
	if (!game)
		return (1);
	if (!parse_map(game))
		return (ft_free(game), 1);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIND_W, WIND_H, "Black Star");
	init_image(game);
	mlx_hook(game->win, 17, 0, ft_exit, game);
	mlx_hook(game->win, 02, (1L << 0), key_press, game);
	mlx_hook(game->win, 03, (1L << 1), key_release, game);
	mlx_loop_hook(game->mlx, render_3d, game);
	mlx_loop(game->mlx);
	ft_free(game);
	return (0);
}
