#include "gol.h"

void print_usage(char *name)
{
	printf("Bad args:\n");
	printf("%s [cell size] [cells count]\n", name);
}

void exit_with(char *s)
{
	printf("game of life failed: %s\n", s);
	exit(1);
}

size_t get_time_ms(void)
{
	struct timeval now;
	size_t result;

	gettimeofday(&now, NULL);
	result = now.tv_sec * 1000;
	result += now.tv_usec / 1000;
	return (result);
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
