#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "bt.h"
#include "bmpl.h"
#include "sdl_events.h"
#include "testmap.h"
#include "colors.h"
#include "alloc.h"

#define TILE_SIZE 20
#define XTILES 40 /* tiles per row */
#define YTILES 30 /* tiles per col */

static SDL_Surface **stocks;
static SDL_Surface *wallpaper;
static int xoffset = 0, yoffset = 0;
static int anim_ticker = 0;
static int file_version = 1;
static map_data *cur_map = NULL;
static union _utile {
    unsigned int as_int;
    unsigned char as_char[4];
} utile;

static void draw_map();
static void on_idle();
static void load_stocks(char *id, int xcount, int ycount);
static SDL_Surface *get_tile(SDL_Surface *src, int x, int y);
static Uint32 switch_anim_ticker(Uint32 interval, void *param);

static void write_int(FILE *fp, unsigned int num);
static unsigned int read_int(FILE *fp);

static void set_stock_id(int xt, int yt, int id);

void init_map()
{
    load_stocks("map.stock1", 40, 30); 
    evl_reg(evl_sdl, EV_SDL_PAINT, draw_map);
    evl_reg(evl_sdl, EV_SDL_IDLE, on_idle);

    /* TODO: load map */
    /*
    cur_map.width      = TM_WIDTH;
    cur_map.height     = TM_HEIGHT;
    cur_map.anim_count = TM_ANIMS;
    cur_map.anim_ticks = TM_TICKS;
    cur_map.anims      = test_anims;
    cur_map.data       = test_map;
    */
    //read_map("main.map");

    //write_map("main.map");
    //read_map("main.map");

    SDL_AddTimer(1000, switch_anim_ticker, NULL);
}

static void swap(unsigned char *c1, unsigned char *c2)
{
    unsigned char tmp;

    tmp = *c1;
    *c1 = *c2;
    *c2 = tmp;
}

static void write_int(FILE *fp, unsigned int num)
{
    int i;

    utile.as_int = num;

    /* write int as 4 chars */
    for (i = 0; i < 4; i++) {
        printf("%.2x ", utile.as_char[i]);
        fputc(utile.as_char[i], fp);
    }

    printf(" = %u\n", utile.as_int);
}

static unsigned int read_int(FILE *fp)
{
    int i;

    /* put tile data into union */
    for (i = 0; i < 4; i++)
        utile.as_char[i] = (unsigned char) fgetc(fp);

    swap(&utile.as_char[0], &utile.as_char[1]);
    swap(&utile.as_char[0], &utile.as_char[3]);

    printf("%.2x%.2x %.2x%.2x = %u\n", utile.as_char[0], utile.as_char[1], utile.as_char[2], utile.as_char[3], utile.as_int);
}

void write_map(char *filename)
{
    int anim, tick, x, y, i;
    FILE *fp;

    if (!cur_map)
        return;

    printf("write map...");
    fp = fopen(filename, "w");
    
    /* write header... */
    fprintf(fp, "MAP:%u,%u,%u,%u,%u\n", file_version, cur_map->width, cur_map->height, cur_map->anim_count, cur_map->anim_ticks);

    /* write anim data */
    for (anim = 0; anim < cur_map->anim_count; anim++) {
        for (tick = 0; tick < cur_map->anim_ticks; tick++) {
            fprintf(fp, "%u.", cur_map->anims[anim * cur_map->anim_count + tick]);
        }
    }
    fputc('\n', fp);

    /* write map data */
    for (y = 0; y < cur_map->height; y++) {
        for (x = 0; x < cur_map->width; x++) {
            /* put tile data into union */
            write_int(fp, cur_map->data[cur_map->width * y + x]);
        }
    }

    fclose(fp);
    printf("ok\n");
}

void fill_map(int id)
{
    int x, y;

    for (y = 0; y < cur_map->height; y++) {
        for (x = 0; x < cur_map->width; x++) {
            cur_map->data[y * cur_map->width + x] = id;
        }
    }
}

void map_new(unsigned int width, unsigned int height, unsigned int anim_count, unsigned int anim_ticks)
{
    printf("create new map structure (%u,%u,%u,%u)...", width, height, anim_count, anim_ticks);

    //TODO: cleanup old map!!

    /* check if cur_map is null */
    if (cur_map == NULL)
        cur_map = MALLOC(map_data);

    /* reserve space for our map */
    cur_map->anims = MALLOC_ARRAY(int, anim_count * anim_ticks);
    cur_map->data = MALLOC_ARRAY(int, width * height);

    /* set attributes */
    cur_map->width = width;
    cur_map->height = height;
    cur_map->anim_count = anim_count;
    cur_map->anim_ticks = anim_ticks;
}


void read_map(char *filename)
{
    int anim, tick, x, y, i, version;
    int width, height, anim_count, anim_ticks;
    FILE *fp;

    printf("read map...");
    fp = fopen(filename, "r");

    /* check if file is available... */
    if (!fp) {
        CON_Out(btConsole, "file not found");
        return;
    }

    /* read header... */
    fscanf(fp, "MAP:%u,%u,%u,%u,%u\n", &version, &width, &height, &anim_count, &anim_ticks);

    /* check version */
    if (version != file_version)
        error("Wrong map version or wrong format.");

    map_new(width, height, anim_count, anim_ticks);

    /* read anim data */
    for (anim = 0; anim < cur_map->anim_count; anim++) {
        for (tick = 0; tick < cur_map->anim_ticks; tick++) {
            fscanf(fp, "%u.", &cur_map->anims[anim * cur_map->anim_count + tick]);
        }
    }
    fseek(fp, 1, SEEK_CUR); /* jump over \n */

    printf("\n");

    /* read map data */
    for (y = 0; y < cur_map->height; y++) {
        for (x = 0; x < cur_map->width; x++) {
            /* write tile data into our struct */
            cur_map->data[cur_map->width * y + x] = read_int(fp);
        }
    }

    fclose(fp);
    exit(0);
    printf("ok (cur_map->data[0] = %u)\n", cur_map->data[0]);
}

static Uint32 switch_anim_ticker(Uint32 interval, void *param)
{
    anim_ticker = !anim_ticker;
    return interval;
}

static void draw_map()
{
    int x, y, x2, y2, id;
    SDL_Rect rect;


    if (cur_map == NULL) {
        /*
        rect.x = 0;
        rect.y = 0;
        SDL_BlitSurface(wallpaper, NULL, screen, &rect);
        */
        return;
    }

    //printf("draw map (%u,%u,%u,%u)...", cur_map->width, cur_map->height, cur_map->anim_count, cur_map->anim_ticks);

    /* consider offsets */
    if (xoffset < 0)
        xoffset = cur_map->width - (cur_map->width % abs(xoffset));

    if (yoffset < 0)
        yoffset = cur_map->height - (cur_map->height % abs(yoffset));

    /* draw testmap */
    for (y = 0; y < YTILES; y++) {
        //printf("y: %u...\n", y);
        rect.y = TILE_SIZE * y;
        for (x = 0; x < XTILES; x++) {
            rect.x = TILE_SIZE * x;

            //printf("%u\n", yoffset);

            if ((y + yoffset) >= cur_map->height)
                y2 = y + (yoffset - cur_map->height);
            else
                y2 = y + yoffset;

            if ((x + xoffset) >= cur_map->width)
                x2 = x + (xoffset - cur_map->width);
            else
                x2 = x + xoffset;

            //printf("data from: %u...", y2 * cur_map->width + x2);
            id = cur_map->data[y2 * cur_map->width + x2];
            if (id & MF_ANIM) {
                /* it's an animation, so we read the current animation tile */
                id = cur_map->anims[(id & MF_ID) + anim_ticker];
            } 

            //printf("blit (%u)...", id);
            SDL_BlitSurface(stocks[id], NULL, screen, &rect);
            //printf("ok\n");
        }
    }
    //printf("ok\n");
}

static void on_idle()
{
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if (CON_isVisible(btConsole))
        return;

    if (cur_map) {
        if ( keystate[SDLK_UP]) {
            if (yoffset > 0) {
                // map up...
                yoffset--;
            }
        } else if (keystate[SDLK_DOWN]) {
            if ((yoffset + YTILES) < (cur_map->height - 1)) {
                // map down...
                yoffset++;
            }
        }

        if (keystate[SDLK_LEFT]) {
            // map left...
            if (xoffset > 0)
                xoffset--;
        } else if (keystate[SDLK_RIGHT]) {
            // map right...
            if ((xoffset + XTILES) < (cur_map->width - 1))
                xoffset++;
        }
    }

    if (cur_map && editor_mode) {
        int x, y, xt, yt;
        Uint8 mousestate = SDL_GetMouseState(&x, &y);

        xt = (x - (x % TILE_SIZE)) / TILE_SIZE;
        yt = (y - (y % TILE_SIZE)) / TILE_SIZE;

        if (mousestate & SDL_BUTTON(1))
            map_put(1, xt, yt);
        else if (mousestate & SDL_BUTTON(3))
            map_put(0, xt, yt);
    }
}

void map_put(int id, int xt, int yt)
{
    if (id) {
        set_stock_id(xt, yt, editor_pen);
    } else {
        if (editor_pg) {
            int x, y;
            for (y = 0; y < editor_pg_y; y++) {
                for (x = 0; x < editor_pg_x; x++) {
                    set_stock_id(xt + x, yt + y, 
                            editor_pg[editor_pg_x * y + x]);
                }
            }
        }
    }
}

static void set_stock_id(int xt, int yt, int id)
{
    /* consider offset */
    xt += xoffset;
    yt += yoffset;

    //printf("%u/%u (%u, %u)\n", xt, yt, xoffset, yoffset);
    cur_map->data[yt * cur_map->width + xt] = id;
}

static void load_stocks(char *id, int xcount, int ycount)
{
    SDL_Surface *tmp;
    /* first we create space for our stocks array */
    stocks = (SDL_Surface**) malloc(sizeof (SDL_Surface*) * xcount * ycount);
    
    /* then we load the stock bitmap */
    tmp = bmpl_get(id);

    /* now we copy create one surface per tile ... copy it from tmp */
    {
        int x, y, i = 0;

        for (y = 0; y < ycount; y++)
            for (x = 0; x < xcount; x++)
               stocks[i++] = get_tile(tmp, x, y);
    }

    SDL_FreeSurface(tmp);
}

static SDL_Surface *get_tile(SDL_Surface *src, int x, int y)
{
    SDL_Surface *tile;
    SDL_Rect srcrect; 

    tile = SDL_CreateRGBSurface(SDL_SWSURFACE, TILE_SIZE, TILE_SIZE, 8, 0, 0, 0, 0); 
    SDL_SetColors(tile, colors, 0, n_colors);

    srcrect.x = x * TILE_SIZE;
    srcrect.y = y * TILE_SIZE;
    srcrect.w = srcrect.x + TILE_SIZE;
    srcrect.h = srcrect.y + TILE_SIZE;

    SDL_BlitSurface (src, &srcrect, tile, NULL);

    return tile;
}
