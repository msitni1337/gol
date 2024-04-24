#include "gol.h"

int get_alive_neighbor_count(int x, int y, int size, t_img *img)
{
	int count;

	count = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (!i && !j)
				continue;
			int row = ((x * size) + (i * size)) % img->width;
			int col = ((y * size) + (j * size)) % img->height;
			if (row < 0)
			{
				row = img->width - 1;
			}
			if (col < 0)
			{
				col = img->height - 1;
			}
			int state = get_img_pixel_at(img, row, col);
			if (state == ALIVE)
				count++;
		}
	}
	return count;
}

void set_cell(int x, int y, int color, t_img *img, t_state *state)
{
	for (int i = 0; i < state->cell_size; i++)
	{
		for (int j = 0; j < state->cell_size; j++)
		{
			set_img_pixel_at(img, x + i, y + j, color);
		}
	}
}

void switch_cell(int mouse_x, int mouse_y, t_state *state)
{
	int color = get_img_pixel_at(&(state->texture[state->swap_buff]), mouse_x, mouse_y);
	if (color == DEAD)
		color = ALIVE;
	else if (color == ALIVE)
		color = DEAD;
	else
		assert(!"IMPOSSIBLE STATE");

	int col = mouse_x / state->cell_size;
	int row = mouse_y / state->cell_size;
	for (int i = 0; i < state->cell_size; i++)
	{
		for (int j = 0; j < state->cell_size; j++)
		{
			set_img_pixel_at(&(state->texture[state->swap_buff]), i + (col * state->cell_size), j + (row * state->cell_size), color);
		}
	}
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

void start_mlx(t_state *state)
{
	state->mlx_context = mlx_init();
	if (!state->mlx_context)
		exit_with("Can't init mlx");
	state->window = mlx_new_window(state->mlx_context,
									 state->win_width, state->win_height, WINDOW_NAME);
	if (!state->window)
		exit_with("Can't create window");
	generate_swap_buffer(state);
	flush_img(&(state->texture[0]), DEAD);
	flush_img(&(state->texture[1]), DEAD);
	mlx_hook(state->window, ON_DESTROY, 0, mlx_loop_end, state->mlx_context);
	mlx_key_hook(state->window, key_hook, state);
	mlx_hook(state->window, ON_MOUSEDOWN, MOUSEDOWN, mouse_hook_down, state);
}
