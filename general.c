#include "gol.h"

void exit_with(char *s)
{
	printf("game of life failed: %s\n", s);
	exit(1);
}

void flush_img(t_img *img, int color)
{
	unsigned char *tmp;

	for (int x = 0; x < img->width; x++)
	{
		for (int y = 0; y < img->height; y++)
		{
			tmp = &(img->data[x * (img->bpp / 8) + y * img->width_size]);
			*(unsigned int *)tmp = color;
		}
	}
}

void set_img_pixel_at(t_img *img, int x, int y, int color)
{
	unsigned char *tmp;

	tmp = &(img->data[x * (img->bpp / 8) + y * img->width_size]);
	*(unsigned int *)tmp = color;
}

unsigned int get_img_pixel_at(t_img *img, int x, int y)
{
	unsigned char *tmp;

	tmp = &(img->data[x * (img->bpp / 8) + y * img->width_size]);

	return *(unsigned int *)tmp;
}

void generate_swap_buffer(t_state *p_state)
{
	t_img *tmp;
	int i;

	i = 0;
	while (i < 2)
	{
		tmp = &(p_state->texture[i]);
		tmp->handle = mlx_new_image(p_state->mlx_context, p_state->win_width, p_state->win_height);
		tmp->data = mlx_get_data_addr(tmp->handle, &tmp->bpp, &tmp->width_size, &tmp->endian);
		tmp->width = p_state->win_width;
		tmp->height = p_state->win_height;
		i++;
	}
	p_state->swap_buff = 0;
}

void start_mlx(t_state *p_state)
{
	p_state->mlx_context = mlx_init();
	if (!p_state->mlx_context)
		exit_with("Can't init mlx");
	p_state->window = mlx_new_window(p_state->mlx_context,
									 p_state->win_width, p_state->win_height, WINDOW_NAME);
	if (!p_state->window)
		exit_with("Can't create window");
	generate_swap_buffer(p_state);
}
