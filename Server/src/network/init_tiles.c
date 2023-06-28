/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** init_tiles.c
*/

#include "../../include/main.h"

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

static void add_resource_random_tile(t_server *server, unsigned *max_resources)
{
    unsigned total_tiles = server->params->width * server->params->height;

    for (unsigned j = 0; j < 7; j++) {
        if (max_resources[j] <= 0)
            continue;
        unsigned tile_index = rand() % total_tiles;
        if (j < TOTAL_RESOURCES)
            TILES(tile_index).resources[j] += 1;
        max_resources[j] -= 1;
    }
}

static void fill_tiles_random(t_server *server, unsigned *max_resources)
{
    bool resources_remaining = true;

    do {
        add_resource_random_tile(server, max_resources);
        resources_remaining = false;
        for (unsigned i = 0; i < 7; i++) {
            if (max_resources[i] > 0) {
                resources_remaining = true;
                break;
            }
        }
    } while (resources_remaining);
}

void generate_food(t_server *server)
{
    unsigned max_resources[7];

    for (unsigned i = 0; i < 7; i++)
        max_resources[i] = calculate_density(server->params, i);
    fill_tiles_random(server, max_resources);
}
