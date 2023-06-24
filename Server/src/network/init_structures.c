/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** init_structures.c
*/

#include "../../include/main.h"
#include "signal.h"
#include <time.h>

/*
for (int i = 0; i < server->params->width * server->params->height; i++) {
    printf("Tile %d: x: %d y: %d | ", i, server->game.tiles[i].x,
    server->game.tiles[i].y);
    printf("food: %d | ", server->game.tiles[i].resources[0]);
    printf("linemate: %d | ", server->game.tiles[i].resources[1]);
    printf("deraumere: %d | ", server->game.tiles[i].resources[2]);
    printf("sibur: %d | ", server->game.tiles[i].resources[3]);
    printf("mendiane: %d | ", server->game.tiles[i].resources[4]);
    printf("phiras: %d | ", server->game.tiles[i].resources[5]);
    printf("thystame: %d\n", server->game.tiles[i].resources[6]);
}
 */

static t_map *set_tiles_struct(t_params *params)
{
    unsigned size = (params->width * params->height);
    unsigned z = 0;
    unsigned j = 0;
    t_map *tiles = (t_map*)calloc((size + 1), sizeof(t_map));

    if (tiles == NULL)
        exit_malloc();
    for (unsigned i = 0; j < size; i++, j++) {
        if (i % params->width == 0 && i != 0)
            i = 0, z++;
        tiles[j].y = z;
        tiles[j].x = i;
        tiles[j].player = 0;
    }
    return tiles;
}

static void set_game_struct_next(t_game *game, t_params *params, int i)
{
    for (int j = 0; j < params->clientsNb; j++) {
        game->teams[i].players[j].pos_x = 0;
        game->teams[i].players[j].pos_y = 0;
        game->teams[i].players[j].is_an_egg = true;
        game->teams[i].players[j].id = -1;
    }
}

/**
 * Set the game struct to 0
 * @param params
 * @return game
 */
static t_game set_game_struct(t_params *params)
{
    t_game game = {0};
    game.teams = (t_teams *)calloc((params->num_teams + 1), sizeof(t_teams));
    if (game.teams == NULL)
        exit_malloc();
    for (int i = 0; i < params->num_teams; i++) {
        game.teams[i].name = strdup(params->team_names[i]);
        if (game.teams[i].name == NULL)
            exit_malloc();
    }
    for (int i = 0; i < params->num_teams; i++) {
        game.teams[i].max_players = params->clientsNb;
        game.teams[i].players = calloc(params->clientsNb + 1, 88UL);
        if (game.teams[i].players == NULL)
            exit_malloc();
        set_game_struct_next(&game, params, i);
    }
    game.tiles = set_tiles_struct(params);
    return game;
}

void set_server_struct_next(t_server *server)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        server->clients[i].id = -1;
        server->clients[i].index_team = -1;
        server->clients[i].index_in_team = -1;
        server->clients[i].is_gui = false;
        server->clients[i].is_forked = false;
        server->clients[i].dead = false;
        server->clients[i].buffer = calloc(1, 1);
        if (server->clients[i].buffer == NULL)
            exit_malloc();
    }
}

/**
 * Set the server struct to 0
 * @param params
 * @return server
 */
t_server *set_server_struct(t_params *params)
{
    t_server *server = (t_server *)calloc(1, sizeof(t_server));
    if (server == NULL)
        exit_malloc();
    server->params = params;
    server->game = set_game_struct(params);
    generate_food(server);
    server->gen_food_timer.start = time(NULL);
    if (server->gen_food_timer.start == -1)
        exit_timer();
    server->gen_food_timer.duration = 20.0 / server->params->freq;
    server->remove_food_timer.start = time(NULL);
    if (server->remove_food_timer.start == -1)
        exit_timer();
    server->remove_food_timer.duration = 126.0 / server->params->freq;
    set_server_struct_next(server);
    printf("Timer remove food: %f\n", server->remove_food_timer.duration);
    for (int i = 0; i < server->params->width * server->params->height; i++) {
        printf("Tile %d: x: %d y: %d | ", i, server->game.tiles[i].x,
               server->game.tiles[i].y);
        printf("food: %d | ", server->game.tiles[i].resources[0]);
        printf("linemate: %d | ", server->game.tiles[i].resources[1]);
        printf("deraumere: %d | ", server->game.tiles[i].resources[2]);
        printf("sibur: %d | ", server->game.tiles[i].resources[3]);
        printf("mendiane: %d | ", server->game.tiles[i].resources[4]);
        printf("phiras: %d | ", server->game.tiles[i].resources[5]);
        printf("thystame: %d\n", server->game.tiles[i].resources[6]);
    }
    return server;
}
