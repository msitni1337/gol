#include "gol.h"

int key_hook(int key, t_state *state)
{
    if (key == KEY_SPACE)
    {
        state->pause_sim = !(state->pause_sim);
    }
    return 0;
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

/*
int mouse_hook_up(int button, int x, int y, t_state *state)
{

}
*/

int mouse_hook_down(int button, int x, int y, t_state *state)
{
    if (!state->pause_sim)
        return 0;
    if (button == MOUSE_LEFT)
    {
        switch_cell(x, y, state);
    }
    return 0;
}

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
            int row = ((x * size) +  (i * size)) % img->width;
            int col = ((y * size) + (j * size)) % img->height;
            if (row < 0)
            {
                continue;
                row = img->width - 1;
            }
            if (col < 0)
            {
                continue;
                col = img->height - 1;
            }
            int state = get_img_pixel_at(img, row, col);
            if (state == ALIVE)
                count++;
        }
    }
    return count;
}

size_t  get_time_ms(void)
{
        struct timeval  now;
        size_t                  result;

        gettimeofday(&now, NULL);
        result = now.tv_sec * 1000;
        result += now.tv_usec / 1000;
        return (result);
}

int game_of_life(t_state *state)
{
    size_t dt = get_time_ms() - state->dt;
    if (!(state->pause_sim) && dt > TIME_TO_SLEEP)
    {
        t_img *curr = &(state->texture[state->swap_buff]);
        t_img *next = &(state->texture[(state->swap_buff + 1) % 2]);

        for (int x = 0; x < state->cells_count; x++)
        {
            for (int y = 0; y < state->cells_count; y++)
            {
                unsigned int cell_state = get_img_pixel_at(curr, x * state->cell_size, y * state->cell_size);
                int alive_neighbors = get_alive_neighbor_count(x, y, state->cell_size, curr);

                if (cell_state == ALIVE)
                {
                    if (alive_neighbors == 2 || alive_neighbors == 3)
                        cell_state = ALIVE;
                    else
                        cell_state = DEAD;
                }
                else if (cell_state == DEAD)
                {
                    if (alive_neighbors == 3)
                        cell_state = ALIVE;
                }
                else
                {
                    exit_with("IMPOSIBLE STATE");
                }
                set_cell(x * state->cell_size, y * state->cell_size, cell_state, next, state);
            }
        }
        state->swap_buff = (state->swap_buff + 1) % 2;
        state->dt = get_time_ms();
    }
    mlx_put_image_to_window(state->mlx_context, state->window, state->texture[state->swap_buff].handle, 0, 0);
    return 0;
}

void print_usage(char *name)
{
    printf("Bad args:\n");
    printf("%s [cell size] [cells count]\n", name);
}

int main(int c, char **v)
{
    t_state state;

    if (c != 3)
    {
        print_usage(v[0]);
        return 1;
    }

    state.cell_size = atoi(v[1]);
    state.cells_count = atoi(v[2]);
    state.win_height = state.cells_count * state.cell_size;
    state.win_width = state.win_height;
    state.dt = get_time_ms();

    if (state.win_height > WIN_CAP)
    {
        printf("Window is too big\n");
        return 1;
    }

    state.pause_sim = 1;
    start_mlx(&state);
    flush_img(&(state.texture[0]), DEAD);
    flush_img(&(state.texture[1]), DEAD);
    mlx_hook(state.window, ON_DESTROY, 0, mlx_loop_end, state.mlx_context);

    mlx_key_hook(state.window, key_hook, &state);
    // mlx_hook(state.window, ON_MOUSEMOVE, POINTERMOVE, mouse_hook_move, &state);
    mlx_hook(state.window, ON_MOUSEDOWN, MOUSEDOWN, mouse_hook_down, &state);
    // mlx_hook(state.window, ON_MOUSEUP, MOUSERELEASE, mouse_hook_up, &state);

    mlx_loop_hook(state.mlx_context, game_of_life, &state);
    mlx_loop(state.mlx_context);
}