/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** init_tiles.c
*/

#include "../../include/server.h"

static unsigned calculate_density(t_params *params, unsigned type)
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

static void add_resource(t_server *server, unsigned i, unsigned tile_index,
int *max_resources)
{
    unsigned total_tiles = server->params->width * server->params->height;

    for (unsigned j = 0; j < 7; j++) {
        if (max_resources[j] < 0)
            continue;
        unsigned max_rsc_on_tile = max_resources[j] / (total_tiles - i) + 1;
        unsigned resource_to_add = rand() % max_rsc_on_tile;
        if (resource_to_add > max_resources[j])
            resource_to_add = max_resources[j];
        if (j < TOTAL_RESOURCES)
            TILES(tile_index).resources[j] += resource_to_add;
        max_resources[j] -= resource_to_add;
    }
}

static void fill_tiles(t_server *server, int *permutation, int *max_resources)
{
    unsigned total_tiles = server->params->width * server->params->height;

    for (unsigned i = 0; i < total_tiles; i++) {
        unsigned tile_index = permutation[i];
        add_resource(server, i, tile_index, max_resources);
    }
}

void generate_food(t_server *server)
{
    unsigned total_tiles = server->params->width * server->params->height;
    unsigned max_resources[7];
    for (unsigned i = 0; i < 7; i++) {
        max_resources[i] = calculate_density(server->params, i);
    }
    unsigned* permutation = (unsigned*)malloc(total_tiles * sizeof(unsigned));
    for (unsigned i = 0; i < total_tiles; i++) {
        permutation[i] = i;
    }
    for (unsigned i = total_tiles - 1; i > 0; i--) {
        unsigned j = rand() % (i + 1);
        unsigned tmp = permutation[i];
        permutation[i] = permutation[j];
        permutation[j] = tmp;
    }
    fill_tiles(server, permutation, max_resources);
}
