/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** main.c
*/

#include "../include/main.h"
#include "signal.h"

/**
 * Set the params struct to 0
 * @return params
 */
t_params set_param_struct(void)
{
    t_params params;
    memset(&params, 0, sizeof(t_params));
    return params;
}

int calculate_density(t_params *params, int type)
{
    switch (type) {
        case 0:
            return (0.5 * params->width * params->height);
        case 1:
            return (0.3 * params->width * params->height);
        case 2:
            return (0.15 * params->width * params->height);
        case 3:
            return (0.1 * params->width * params->height);
        case 4:
            return (0.1 * params->width * params->height);
        case 5:
            return (0.08 * params->width * params->height);
        case 6:
            return (0.05 * params->width * params->height);
        default:
            return 0;
    }
}

void generate_food(t_server *server)
{
    int total_tiles = server->params->width * server->params->height;
    int max_resources[7];
    for (int i = 0; i < 7; i++) {
        max_resources[i] = calculate_density(server->params, i);
    }
    int* permutation = malloc(total_tiles * sizeof(int));
    for (int i = 0; i < total_tiles; i++) {
        permutation[i] = i;
    }
    for (int i = total_tiles - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = permutation[i];
        permutation[i] = permutation[j];
        permutation[j] = temp;
    }
    for (int i = 0; i < total_tiles; i++) {
        int tile_index = permutation[i];
        for (int j = 0; j < 7; j++) {
            if (max_resources[j] > 0) {
                int max_resource_per_tile = max_resources[j] / (total_tiles - i) + 1;
                int resource_to_add = rand() % max_resource_per_tile;
                if (resource_to_add > max_resources[j]) {
                    resource_to_add = max_resources[j];
                }
                switch (j) {
                    case 0: server->game.tiles[tile_index].resources[FOOD] += resource_to_add; break;
                    case 1: server->game.tiles[tile_index].resources[LINEMATE] += resource_to_add; break;
                    case 2: server->game.tiles[tile_index].resources[DERAUMERE] += resource_to_add; break;
                    case 3: server->game.tiles[tile_index].resources[SIBUR] += resource_to_add; break;
                    case 4: server->game.tiles[tile_index].resources[MENDIANE] += resource_to_add; break;
                    case 5: server->game.tiles[tile_index].resources[PHIRAS] += resource_to_add; break;
                    case 6: server->game.tiles[tile_index].resources[THYSTAME] += resource_to_add; break;
                }
                max_resources[j] -= resource_to_add;
            }
        }
    }
}

t_map *set_tiles_struct(t_params *params)
{
    t_map *tiles = malloc(((params->width * params->height) + 1) * sizeof(t_map));
    if (tiles == NULL) {
        perror("Failed to allocate memory for tiles");
        exit(EXIT_FAILURE);
    }
    memset(tiles, 0, (((params->width * params->height) + 1) * sizeof(t_map)));
    int z = 0;
    int j = 0;
    for (int i = 0; j < (params->width * params->height); i++, j++) {
        if (i % params->width == 0 && i != 0) {
            i = 0;
            z++;
        }
        tiles[j].y = z;
        tiles[j].x = i;
        tiles[j].player = 0;
    }
    return tiles;
}

/**
 * Set the game struct to 0
 * @param params
 * @return game
 */
t_game set_game_struct(t_params *params)
{
    t_game game = {0};
    game.teams = malloc((params->num_teams + 1) * sizeof(t_teams));
    if (game.teams == NULL) {
        perror("Failed to allocate memory for teams");
        exit(EXIT_FAILURE);
    }
    memset(game.teams, 0, ((params->num_teams + 1) * sizeof(t_teams)));
    for (int i = 0; i < params->num_teams; i++) {
        game.teams[i].name = strdup(params->team_names[i]);
    }
    for (int i = 0; i < params->num_teams; i++) {
        game.teams[i].max_players = params->clientsNb;
        game.teams[i].players = malloc(params->clientsNb * sizeof(t_client));
        if (game.teams[i].players == NULL) {
            perror("Failed to allocate memory for players");
            exit(EXIT_FAILURE);
        }
        memset(game.teams[i].players, 0, params->clientsNb * sizeof(t_client));
        for (int j = 0; j < params->clientsNb; j++) {
            game.teams[i].players[j].pos_x = 0;//RANDINT(0, params->width - 1);
            game.teams[i].players[j].pos_y = 0;//RANDINT(0, params->height - 1);
            game.teams[i].players[j].is_an_egg = true;
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
    t_server *server = malloc(sizeof(t_server));
    if (server == NULL) {
        perror("Failed to allocate memory for server");
        exit(EXIT_FAILURE);
    }
    server->max_fd = 0;
    server->sockfd = 0;
    memset(server->clients, 0, MAX_CLIENTS * sizeof(t_client));
    server->params = params;
    server->game = set_game_struct(params);
    generate_food(server);
    //print map
    for (int i = 0; i < (params->width * params->height); i++) {
        printf("Tile %d : x = %d, y = %d, food = %d, linemate = %d, deraumere = %d, sibur = %d, mendiane = %d, phiras = %d, thystame = %d\n",
               i,
               server->game.tiles[i].x,
               server->game.tiles[i].y,
               server->game.tiles[i].resources[FOOD],
               server->game.tiles[i].resources[LINEMATE],
               server->game.tiles[i].resources[DERAUMERE],
               server->game.tiles[i].resources[SIBUR],
               server->game.tiles[i].resources[MENDIANE],
               server->game.tiles[i].resources[PHIRAS],
               server->game.tiles[i].resources[THYSTAME]
        );
    }
    return server;
}

/**
 * Set the params struct to 0
 * @param server
 * @param new_socket
 * @param readfds
 */
void add_client(t_server *server, int new_socket)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].socket_fd == 0) {
            server->clients[i].socket_fd = new_socket;
            server->id = i;
            printf("New client connected : %d\n", new_socket);
            break;
        }
    }
}

void read_data_from_server(t_server *svr)
{
    char buffer[1025];
    int valread;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        int sd = svr->clients[i].socket_fd;

        if (sd == 0)
            continue;
        if (FD_ISSET(sd, &svr->readfds)) {
            handle_client_data(svr, sd);
        }
    }
}

void handle_new_connection(t_server *svr)
{
    int new_socket;

    if (FD_ISSET(svr->sockfd, &svr->readfds)) {
        if ((new_socket = accept(svr->sockfd, NULL, NULL)) >= 0) {
            add_client(svr, new_socket);
            send_to_client(svr, "WELCOME\n", svr->id);
        }
    }
}

int set_fds(t_server *svr)
{
    FD_ZERO(&svr->readfds);
    svr->max_fd = svr->sockfd;

    FD_SET(svr->sockfd, &svr->readfds);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        int sd = svr->clients[i].socket_fd;
        if (sd > 0) {
            FD_SET(sd, &svr->readfds);
        }
        if (sd > svr->max_fd)
            svr->max_fd = sd;
    }
    return svr->max_fd;
}

int main(int ac, char **av)
{
    if (ac == 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
        printf("%s\n", HELP);
        return EXIT_SUCCESS;
    }
    srand(time(NULL));
    t_params params = set_param_struct();
    parse_args(ac, av, &params);
    check_params(&params);
    t_server *server = set_server_struct(&params);

    setup_server(server, &params);
    while (true) {
        signal(SIGPIPE, SIG_IGN);
        int activity = select(set_fds(server) + 1, &server->readfds, NULL, NULL, NULL);
        if (activity < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        }
        handle_new_connection(server);
        read_data_from_server(server);
    }
    return EXIT_SUCCESS;
}
