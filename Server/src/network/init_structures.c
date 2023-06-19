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
for (int i = 0; i < svr->params->width * svr->params->height; i++) {
    printf("Tile %d: x: %d y: %d | ", i, svr->game.tiles[i].x, svr->game.tiles[i].y);
    printf("food: %d | ", svr->game.tiles[i].resources[0]);
    printf("linemate: %d | ", svr->game.tiles[i].resources[1]);
    printf("deraumere: %d | ", svr->game.tiles[i].resources[2]);
    printf("sibur: %d | ", svr->game.tiles[i].resources[3]);
    printf("mendiane: %d | ", svr->game.tiles[i].resources[4]);
    printf("phiras: %d | ", svr->game.tiles[i].resources[5]);
    printf("thystame: %d\n", svr->game.tiles[i].resources[6]);
}
 */

static t_map *set_tiles_struct(t_params *params)
{
    unsigned size = (params->width * params->height);
    t_map *tiles = (t_map*)calloc((size + 1), sizeof(t_map));
    unsigned z = 0;
    unsigned j = 0;

    if (tiles == NULL)
        perror("Failed to allocate memory for tiles"), exit(EXIT_FAILURE);
    for (unsigned i = 0; j < size; i++, j++) {
        if (i % params->width == 0 && i != 0)
            i = 0, z++;
        tiles[j].y = z;
        tiles[j].x = i;
        tiles[j].player = 0;
    }
    return tiles;
}

/**
 * Set the params struct to 0
 * @return params
 */
t_params set_param_struct(void)
{
    t_params params = {0};
    return params;
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
        perror("Failed to allocate memory for teams"), exit(EXIT_FAILURE);
    for (int i = 0; i < params->num_teams; i++)
        game.teams[i].name = strdup(params->team_names[i]);
    for (int i = 0; i < params->num_teams; i++) {
        game.teams[i].max_players = params->clientsNb;
        game.teams[i].players = (t_client *)calloc(params->clientsNb + 1, 88UL);
        if (game.teams[i].players == NULL)
            perror("Failed to allocate memory for ply"), exit(EXIT_FAILURE);
        for (int j = 0; j < params->clientsNb; j++) {
            game.teams[i].players[j].pos_x = 0;//RANDINT(0, params->width - 1);
            game.teams[i].players[j].pos_y = 0;//RANDINT(0, params->height - 1);
            game.teams[i].players[j].is_an_egg = true;
            game.teams[i].players[j].id = -1;
        }
    }
    game.tiles = set_tiles_struct(params);
    return game;
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
        perror("Failed to allocate memory for server"), exit(EXIT_FAILURE);
    server->params = params;
    server->game = set_game_struct(params);
    generate_food(server);
    server->gen_food_timer.start = time(NULL);
    server->gen_food_timer.duration = 20.0 / server->params->freq;
    server->remove_food_timer.start = time(NULL);
    server->remove_food_timer.duration = 126.0 / server->params->freq;
    for (int i = 0; i < SOMAXCONN; i++) {
        server->clients[i].id = -1;
        server->clients[i].index_team = -1;
        server->clients[i].index_in_team = -1;
    }
    printf("Timer remove food: %f\n", server->remove_food_timer.duration);
    return server;
}

void init(void)
{
    printf("Server is starting...\n");
    srand(time(NULL));
    signal(SIGPIPE, SIG_IGN);
}
