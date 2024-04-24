#ifndef GOL_H
#define GOL_H

#define WINDOW_NAME "Game Of Life"
#define ALIVE 0xFFFFFFFF
#define DEAD 0xFF000000
#define TIME_TO_SLEEP 10
#define WIN_CAP 1000

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/time.h>
#include "mlx.h"


typedef struct state
{
    void *mlx_context;
    void *window;

    int win_height;
    int win_width;
	t_img texture[2];
	int swap_buff;

    size_t cells_count;
    size_t cell_size;

    size_t dt;

    int pause_sim;
} t_state;


// general:
void start_mlx(t_state *p_state);
void set_cell(int x, int y, int color, t_img *img, t_state *state);
void switch_cell(int mouse_x, int mouse_y, t_state *state);
int get_alive_neighbor_count(int x, int y, int size, t_img *img);

// input:
int mouse_hook_down(int button, int x, int y, t_state *state);
int key_hook(int key, t_state *state);

// utils:
void exit_with(char*s);
void flush_img(t_img *img, int color);
size_t get_time_ms(void);
void print_usage(char *name);
unsigned int get_img_pixel_at(t_img*img, int x, int y);
void set_img_pixel_at(t_img*img, int x, int y, int color);


#endif