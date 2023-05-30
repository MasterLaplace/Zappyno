/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_join_ai.c
*/

#include "../../../include/send_package.h"

/*
 * struct PACKED JoinAI {
 *    uint8_t command_id;
 * } JoinAI;
 */

static JoinAI set_join_ai_struct(t_server *server) {
    JoinAI join_ai = {0};
    join_ai.avalaible = true;
    printf("index team: %d\n", server->index_team);
    printf("team name: %s\n", server->game.teams[server->index_team].name);
    strcpy(join_ai.team_name, server->game.teams[server->index_team].name);
    return join_ai;
}

void send_join_ai(t_server *server) {
    Package_t package;
    JoinAI join_ai = set_join_ai_struct(server);
    package.command_id = JOIN_AI;
    package.size = htons(sizeof(JoinAI));
    send_to_client(&server->clients[server->id], &package, &join_ai, sizeof(JoinAI));
}

void send_join_ai_to_all(t_server *server)
{
    Package_t package = {0};
    JoinAI join_ai = set_join_ai_struct(server);
    package.command_id = JOIN_AI;
    package.size = htons(sizeof(JoinAI));
    printf("package size: %d\n", ntohs(package.size));
    printf("join_ai size: %ld\n", sizeof(JoinAI));
    //print join_ai
    for (int i = 0; i < sizeof(JoinAI); i++)
        printf("%d ", ((char *)&join_ai)[i]);
    printf("ok\n");
    send_to_all_clients(server->clients, &package, &join_ai, sizeof(JoinAI));
}