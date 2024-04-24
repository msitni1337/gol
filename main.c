#include "gol.h"

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
	mlx_loop_hook(state.mlx_context, game_of_life, &state);
	mlx_loop(state.mlx_context);
}