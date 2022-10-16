#include <stdbool.h>

typedef struct node {
    void *data;
    struct node *prev;
    struct node *next;
} Node;

typedef struct deque {
    int size;
    Node *first;
    Node *last;
    bool reversed;
} Deque;

void print_void_int(void *p);
void print_void_float(void *p);
void print_void_char(void *p);

Deque *create();
void push(Deque *deque, void* data);
void push_front(Deque* deque, void* data);
void *pop(Deque *deque);
void *pop_front(Deque* deque);
int size(Deque *deque);
bool is_empty(Deque *deque);
void reverse(Deque *deque);
void print_deque(Deque *deque, void(*printFunc)(void*));
void destroy(Deque* deque);