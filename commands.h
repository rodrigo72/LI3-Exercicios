#define MAX_ARGS 10

typedef struct cmd {
    char *command;
    int *args; // NULL se não houver
    int nargs; // Número de argumentos
} Cmd;

void process_command(Deque *deque, Cmd* cmd);
Cmd *parse_line(char* line);