#include "deque.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void process_command(Deque *deque, Cmd *cmd) {
    assert(deque != NULL && cmd != NULL);

    char *str = cmd->command;
    if (strcmp("POP", str) == 0) {
        void *ptr = pop(deque);
        if (ptr != NULL) print_void_int(ptr);
        else printf("EMPTY");
        printf("\n");
    } else if (strcmp("POP_FRONT", str) == 0) {
        void *ptr = pop(deque);
        if (ptr != NULL) print_void_int(ptr);
        else printf("EMPTY");
        printf("\n");
    } else if (strcmp("PUSH", str) == 0) {
        for (int i = 0; i < cmd->nargs; i++) push(deque, &cmd->args[i]);
    } else if (strcmp("PUSH_FRONT", str) == 0) {
        for (int i = 0; i < cmd->nargs; i++) push_front(deque, &cmd->args[i]);
    } else if (strcmp("PRINT", str) == 0) {
        print_deque(deque, print_void_int);
    } else if (strcmp("REVERSE", str) == 0) {
        reverse(deque);
    } else if (strcmp("SIZE", str) == 0) {
        printf("%d\n", size(deque));
    }

    free(cmd);
}

void process_command_2(Deque *deque, Cmd* cmd) {
    assert(deque != NULL);
    assert(cmd != NULL);

    typedef struct {
        char *command;
        void (*fn)();
        void *(*fn2)();
        int (*fn3)();
    } command_table_entry;

    command_table_entry command_table[] = {
        {"PUSH", push},
        {"PUSH_FRONT", push_front},
        {"POP", NULL, pop, NULL},
        {"POP_FRONT", NULL, pop_front},
        {"SIZE", NULL, NULL, size},
        {"REVERSE", reverse},
        {"PRINT", print_deque}
    };

    int size = sizeof(command_table)/sizeof(command_table[0]);

    for (int i = 0; i < size; ++i) {
        if (strcmp(cmd->command, command_table[i].command) == 0) {

            if (strcmp(command_table[i].command, "PRINT") == 0) {
                command_table[i].fn(deque, print_void_int);
                printf("\n");
            } else if (command_table[i].fn != NULL) {
                for (int j = 0; j < cmd->nargs; j++) command_table[i].fn(deque, &cmd->args[j]);
            } else if (command_table[i].fn2 != NULL) {
                void *ptr = command_table[i].fn2(deque);
                if (ptr == NULL) printf("EMPTY");
                else print_void_int(ptr);
                printf("\n");
            } else {
                printf("%d\n", command_table[i].fn3(deque));
            }
        }
    }

    free(cmd);
}

Cmd *parse_line(char* line) {
    Cmd *cmd_struct = malloc(sizeof(struct cmd));
    cmd_struct->args = malloc(sizeof(int)*MAX_ARGS);
    cmd_struct->nargs = 0;
    
    char *r = strdup(line);
    char *tok = r, *end = r;

    if (tok != NULL) {
        strsep(&end, " ");
        cmd_struct->command = strdup(tok);
        tok = end;
    }
    
    while (tok != NULL) {
        strsep(&end, " ");
        cmd_struct->args[cmd_struct->nargs] = strtol(tok, NULL, 10);
        cmd_struct->nargs++;
        tok = end;
    }

    free(r);
    return cmd_struct;
}