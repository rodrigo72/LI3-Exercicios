#include "deque.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>

void test_deque_manually(Deque *d) {

    int i = 0;
    int op, op2 = 1;
    int elem[50];
    printf("\e[1;1H\e[2J");

    while(op2 == 1) {
        printf("1 - push\n2 - pop\n3 - push_front\n4 - pop_front\n5 - reverse\n6 - quit\n> ");
        scanf("%d", &op);
        printf("\n");

        switch (op) {
            case 1: {
                printf("Elemento para adicionar: ");
                scanf("%d", &elem[i]);
                push(d, &elem[i]);
                printf("\e[1;1H\e[2J");
                print_deque(d, print_void_int);
                printf("Size: %d\n\n", size(d));
                i++;
                break;
            }
            case 2: {
                pop(d);
                printf("\e[1;1H\e[2J");
                print_deque(d, print_void_int);
                printf("Size: %d\n\n", size(d));
                break;
            }
            case 3: {
                printf("Elemento para adicionar: ");
                scanf("%d", &elem[i]);
                push_front(d, &elem[i]);
                printf("\e[1;1H\e[2J");
                print_deque(d, print_void_int);
                printf("Size: %d\n\n", size(d));
                i++;
                break;
            }
            case 4: {
                pop_front(d);
                printf("\e[1;1H\e[2J");
                print_deque(d, print_void_int);
                printf("Size: %d\n\n", size(d));
                break;
            }
            case 5: {
                reverse(d);
                printf("\e[1;1H\e[2J");
                print_deque(d, print_void_int);
                printf("Size: %d\n\n", size(d));
                break;
            }
            case 6: {
                op2 = 0;
                break;
            }
            default:
                break;
        }
    }

    destroy(d);
}

int main(int argc, char **argv) {
    
    Deque *deque = create();
    FILE *fp = NULL;

    char * line = NULL;
    size_t len;
    ssize_t read;
    
    if (argc < 2) {
        fp = stdin;
    } else {
        char *filename = argv[1];
        fp = fopen(filename, "r");
        if (fp == NULL) {
            perror("Error");
            return 2;
        } 
    }

    while((read = getline(&line, &len, fp)) != -1) {
        if (line[read-1] == '\n') line[read-1] = '\0';
        Cmd *command = parse_line(line);
        process_command(deque, command);
    }
        
    free(line);
    destroy(deque);

    return 0;
}