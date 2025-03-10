# include "cub.h"

t_img   create_img(t_game *game, int width, int height)
{
    t_img image;

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
void    my_put_pixel(t_img image, int x, int y, int color)
{
    char    *pxl_pos;

    if ((x >= 0 && x <= image.width) && (y >= 0 && y <= image.height))
    {
        pxl_pos = image.img_addr + (y * image.size_line + x * (image.bpp / 8));
		*(unsigned int *) pxl_pos = color;
    }
}

void    draw_square(t_img image, int x, int y, int color)
{
    int i;
    int j;

    j = -1;
    while (++j < TILE_SIZE)
    {
        i = -1;
        while (++i < TILE_SIZE)
        {
            my_put_pixel(image, x + i, y + j, color);
        }
    }
}
void    fill_map(t_img image, int ceiling, int floor)
{
    int i;
    int j;

    j = -1;
    while (++j <= (WIND_H / 2))
    {
        i = -1;
        while (++i <= WIND_W)
        {
            my_put_pixel(image, i, j, ceiling);
        }
    }
    while (++j <= WIND_H)
    {
        i = -1;
        while (++i <= WIND_W)
        {
            my_put_pixel(image, i, j, floor);
        }
    }
}

void    draw_player(t_img image, int x, int y, int color)
{
    int i;
    int j;

    j = -1;
    while (++j < (TILE_SIZE / 2))
    {
        i = -1;
        while (++i < (TILE_SIZE / 2))
        {
            my_put_pixel(image, x + i, y + j, color);
        }
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