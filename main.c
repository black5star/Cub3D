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
	if ((ray <= PI / 2) && wall_checker(game, x, y + 1))
		game->flag = 'E';
	if ((ray <= PI / 2) && wall_checker(game, x - 1, y))
		game->flag = 'N';
	if ((ray <= PI && ray > PI / 2) && wall_checker(game, x, y + 1))
		game->flag = 'W';
	if ((ray <= PI && ray > PI / 2) && wall_checker(game, x + 1, y))
		game->flag = 'N';
	if ((ray > PI && ray <= 3 * PI / 2) && wall_checker(game, x, y - 1))
		game->flag = 'W';
	if ((ray > PI && ray <= 3 * PI / 2) && wall_checker(game, x + 1, y))
		game->flag = 'S';
	if ((ray > 3 * PI / 2) && wall_checker(game, x, y - 1))
		game->flag = 'E';
	if ((ray > 3 * PI / 2) && wall_checker(game, x - 1, y))
		game->flag = 'S';
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
	dx = 0;
	while (x >= 0 && x < WIND_W && y >= 0 && y < WIND_H)
	{
		if (wall_checker(game, x, y))
		{
			detect_direction(game, x, y, ray);
			break;
		}
		dx++;
		// my_put_pixel(game->image, x, y, GREEN);
		x += x_inc;
		y += y_inc;
	}
	return (round(dx));
}
int can_move(t_game *game, int x, int y)
{
	int i;
	int j;

	j = y - (TILE_SIZE / 4);
	while(j <= (y + (TILE_SIZE / 4)))
	{
		i = x - (TILE_SIZE / 4);
		while(i <= (x + (TILE_SIZE / 4)))
		{
			if (wall_checker(game, i, j))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

void	vertical_line(t_game *game, double dist, int nbr)
{
	double step;
	double wall_h;
	double x;
	double y;

	step = (WIND_W * ANG_STEP) / FOV;
	wall_h = (WIND_H * WALL_H) / (dist);
	x = step * nbr;
	while (step >= 0)
	{
		y = round(WIND_H / 2) - (wall_h / 2);
		while (y <= round((WIND_H / 2) + (wall_h / 2)))
		{
			if(game->flag == 'S' || game->flag == 'N')
				my_put_pixel(game->image, x, y, wall_COLOR);
			else
				my_put_pixel(game->image, x, y, WALL_COLOR);
			y++;
		}
		step--;
		x++;
	}
}
void	ray_cast(t_game *game, int x, int y, double ray)
{
	double i;
	int nbr;
	double dist;
	double angle;

	i = 0;
	angle = ray - (dgr_to_rad(FOV / 2));
	nbr = 0;
	while (i <= FOV)
	{
		dist = dda_line_drawing(game, x, y, angle);
		vertical_line(game, dist, nbr);
		nbr++;
		i += ANG_STEP;
		angle += dgr_to_rad(ANG_STEP);
	}
}

void	render_3d(t_game *game)
{
	fill_map(game->image, CEILLING, BLACK);
	ray_cast(game, game->px + (TILE_SIZE / 4), game->py + (TILE_SIZE / 4), game->pa);
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
			// 	draw_square(game->image, i * TILE_SIZE, j * TILE_SIZE, WHITE);
			// else
			// 	draw_square(game->image, i * TILE_SIZE, j * TILE_SIZE, WHITE);
			if (game->map[j][i] == game->pv)
				game->map[j][i] = '0';
		}
	}
	// draw_player(game->image, game->px, game->py, PLAYER_COLOR);
	fill_map(game->image, CEILLING, BLACK);
	ray_cast(game, game->px + (TILE_SIZE / 4), game->py + (TILE_SIZE / 4), game->pa);
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
		render_3d(game);
		mlx_put_image_to_window(game->mlx, game->win , game->image.img_ptr, 0, 0);
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
		render_3d(game);
		mlx_put_image_to_window(game->mlx, game->win, game->image.img_ptr, 0, 0);
	}
}

void	to_right(t_game *game)
{
	double	x;
	double	y;

	x = round(sin(game->pa) * SPEED);
	y = round(cos(game->pa) * SPEED);
	if (!can_move(game, game->px - x, game->py + y))
	{
		game->px -= x;
		game->py += y;
		render_3d(game);
		mlx_put_image_to_window(game->mlx, game->win, game->image.img_ptr, 0, 0);
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
		render_3d(game);
		mlx_put_image_to_window(game->mlx, game->win, game->image.img_ptr, 0, 0);
	}
}

void	turn_left(t_game *game)
{
	game->pa -= dgr_to_rad(ANG_STEP + 3);
	if (game->pa <= 0)
		game->pa += (2 * PI);
	render_3d(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img_ptr, 0, 0);
}

void	turn_right(t_game *game)
{
	game->pa += dgr_to_rad(ANG_STEP + 3);
	if (game->pa >= (2 * PI))
		game->pa -= (2 * PI);
	render_3d(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img_ptr, 0, 0);
}

int	ft_key_hook(int key_code, t_game *game)
{
	if (key_code == 65307)
		ft_exit(game);
	if (key_code == 'w')
		go_up(game);
	if (key_code == 's')
		go_down(game);
	if (key_code == 'd')
		to_right(game);
	if (key_code == 'a')
		to_left(game);
	if (key_code == 65361)
		turn_left(game);
	if (key_code == 65363)
		turn_right(game);
	return (1);
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
	game->image = create_img(game, WIND_W, WIND_H);
	render_map(game);
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
	mlx_hook(game->win, 2, (1L << 0), ft_key_hook, game);
	mlx_hook(game->win, 17, 0, ft_exit, game);
	mlx_loop(game->mlx);
	ft_free(game);
	return (0);
}
