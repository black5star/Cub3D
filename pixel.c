#include "cub.h"

void	color_convertor(t_game *game)
{
	game->c_color = game->ceiling[0] << 16 | game->ceiling[1] << 8
		| game->ceiling[2];
	game->f_color = game->floor[0] << 16 | game->floor[1] << 8
		| game->floor[2];
}

t_img	create_img(t_game *game, int width, int height)
{
	t_img	image;

	image.img_ptr = mlx_new_image(game->mlx, width, height);
	image.img_addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
			&(image.size_line), &(image.endian));
	image.width = width;
	image.height = height;
	return (image);
}

t_img	new_file_img(char *path, t_game *game)
{
	t_img		image;
	static int	i;

	image.win = game;
	image.img_ptr = mlx_xpm_file_to_image(game->mlx,
			path, &image.width, &image.height);
	if (!image.img_ptr)
		write(2, "File could not be read\n", 23);
	else
		image.img_addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
				&(image.size_line), &(image.endian));
	i++;
	return (image);
}

void	my_put_pixel(t_img image, int x, int y, int color)
{
	char	*pxl_pos;

	if ((x >= 0 && x <= image.width) && (y >= 0 && y <= image.height))
	{
		pxl_pos = image.img_addr + (y * image.size_line + x * (image.bpp / 8));
		*(unsigned int *) pxl_pos = color;
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > img.size_line)
		x = x % img.size_line;
	if (y > img.height)
		y = y % img.height;
	return (*(unsigned int *)((img.img_addr
			+ (y * img.size_line) + (x * img.bpp / 8))));
}
