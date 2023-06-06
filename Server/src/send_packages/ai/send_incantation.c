/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_incantation.c
*/

#include "../../../include/send_package.h"

int required_ressources[8][8] = {
        //level | nb of player| linen| dera| sibu| mend| phir| thys
        {1, 1, 1, 0, 0, 0, 0, 0},  // for level 1
        {2, 2, 1, 1, 1, 0, 0, 0},  // for level 2
        {3, 2, 2, 0, 1, 0, 2, 0},  // for level 3
        {4, 4, 1, 1, 2, 0, 1, 0},  // for level 4
        {5, 4, 1, 2, 1, 3, 0, 0},  // for level 5
        {6, 6, 1, 2, 3, 0, 1, 0},  // for level 6
        {7, 6, 2, 2, 2, 2, 2, 1}   // for level 7
};

void freeze_participating_players(t_server *server, t_client* player)
{
    int level = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;
    // Get the tile where the player is located
    int x = player->pos_x;
    int y = player->pos_y;
    int tile_index = find_tile(server, x, y);

    // Freeze all players on the tile
    for (int j = 0; j < server->params->num_teams; j++) {
        for (int i = 0; i < server->game.teams[j].max_players; i++) {
            if (server->game.teams[j].players[i].pos_x == x &&
                server->game.teams[j].players[i].pos_y == y &&
                (level + 1) == server->game.teams[j].players[i].level) {
                server->game.teams[j].players[i].is_freezed = true;
            }
        }
    }
}

void perform_elevation(t_server *server)
{
    int level = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;
    // Get the current player initiating the incantation
    t_client* player = &server->clients[server->id];

    // Get the tile where the player is located
    int x = player->pos_x;
    int y = player->pos_y;

    // Increase the level of all participating players
    for (int j = 0; j < server->params->num_teams; j++) {
        for (int i = 0; i < server->game.teams[j].max_players; i++) {
            if (server->game.teams[j].players[i].pos_x == x &&
                server->game.teams[j].players[i].pos_y == y &&
                (level + 1) == server->game.teams[j].players[i].level) {
                server->game.teams[j].players[i].level++;
                server->game.teams[j].players[i].is_freezed = false;
            }
        }
    }


    for (int j = 0; j < server->params->num_teams; j++) {
        for (int i = 0; i < server->game.teams[j].max_players; i++) {
            if (server->game.teams[j].players[i].pos_x == x &&
                server->game.teams[j].players[i].pos_y == y &&
                (level + 1) == server->game.teams[j].players[i].level) {
                send_to_client(server, "Current level: ++", server->game.teams[j].players[i].id);
            }
        }
    }
}

void remove_required_resources(t_server *server)
{
    int level = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;
    // Get the current player initiating the incantation
    t_client* player = &server->clients[server->id];

    // Get the tile where the player is located
    int x = player->pos_x;
    int y = player->pos_y;
    int pos = find_tile(server, x, y);

    // Remove the required resources from the tile
    for (int j = 0; j < server->params->num_teams; j++) {
        for (int i = 0; i < server->game.teams[j].max_players; i++) {
            if (server->game.teams[j].players[i].pos_x == x &&
                server->game.teams[j].players[i].pos_y == y &&
                (level + 1) == server->game.teams[j].players[i].level) {
                for (int k = 1; k < TOTAL_RESOURCES; k++) {
                    if (server->game.tiles[pos].resources[k] >= required_ressources[level][k + 1]) {
                        server->game.tiles[pos].resources[k] -= required_ressources[level][k + 1];
                    }
                }
            }
        }
    }
}

bool verify_elevation_conditions(t_server *server)
{
    int level = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;
    // Verify the number of players on the tile
    int nb_players = 0;
    int x = server->clients[server->id].pos_x;
    int y = server->clients[server->id].pos_y;
    int pos = find_tile(server, x, y);
    for (int j = 0; j < server->params->num_teams; j++) {
        for (int i = 0; i < server->game.teams[j].max_players; i++) {
            if (server->game.teams[j].players[i].pos_x == x &&
                server->game.teams[j].players[i].pos_y == y &&
                (level + 1) == server->game.teams[j].players[i].level) {
                nb_players++;
            }
        }
    }
    printf("nb_player: %d | required: %d\n", nb_players, required_ressources[level][1]);
    if (nb_players < required_ressources[level][1]) {
        printf("nb_players: %d\n", nb_players);
        return false;
    }

    for (int j = 0; j < server->params->num_teams; j++) {
        for (int i = 0; i < server->game.teams[j].max_players; i++) {
            if (server->game.teams[j].players[i].pos_x == x &&
                server->game.teams[j].players[i].pos_y == y &&
                (level + 1) == server->game.teams[j].players[i].level) {
                for (int k = 1; k < TOTAL_RESOURCES; k++) {
                    if (server->game.tiles[pos].resources[k] < required_ressources[level][k + 1]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void send_incantation(t_server *server)
{
    printf("incantation\n");
    // Get the current player initiating the incantation
    t_client* player = &server->clients[server->id];

    // Get the tile where the player is located
    int x = player->pos_x;
    int y = player->pos_y;
    int tile_index = find_tile(server, x, y);

    // Verify the conditions for the elevation ritual at the beginning
    if (!verify_elevation_conditions(server)) {
        // Conditions not met, send failure message to the player
        send_to_client(server, "ko\n", server->id);
        return;
    }

    // Freeze all participating players during the ritual
    freeze_participating_players(server, player);

    // Perform the elevation by increasing the level of all participating players
    perform_elevation(server);

    // Remove the required resources from the tile
    remove_required_resources(server);
}
