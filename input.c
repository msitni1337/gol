#include "gol.h"

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

int key_hook(int key, t_state *state)
{
    if (key == KEY_SPACE)
    {
        state->pause_sim = !(state->pause_sim);
    }
    return 0;
}