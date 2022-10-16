#include "deque.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void print_void_int(void *p) {
    printf("%d ", *(int *)p);
}

void print_void_float(void *p) {
    printf("%f ", *(float *)p);
}

void print_void_char(void *p) {
    printf("%c ", *(char *)p);
}

Deque *create() {
    Deque* deque = malloc(sizeof(struct deque));
    deque->size = 0;
    deque->first = NULL;
    deque->last = NULL;
    deque->reversed = false;
    return deque;
}

static void proper_push(Deque *deque, void *data) {
    assert(deque != NULL);

    Node *new = malloc(sizeof(struct node));
    new->data = data;

    new->prev = deque->last;
    new->next = NULL;
    deque->last = new;

    if (deque->size == 0) {
        deque->first = new;
    } else {
        new->prev->next = new;
    }
    deque->size++;
}

static void proper_push_front(Deque *deque, void *data) {
    assert(deque != NULL);

    Node *new = malloc(sizeof(struct node));
    new->data = data;
    
    new->next = deque->first;
    new->prev = NULL;
    deque->first = new;

    if (deque->size == 0) {
        deque->last = new;
    } else {
        new->next->prev = new;
    }

    deque->size++;
}

static void *proper_pop(Deque* deque) {
    assert(deque != NULL);

    if (deque->size == 0) {
        return NULL;
    }

    Node *last = deque->last;
    void *last_data = last->data;
    deque->last = last->prev;

    if (deque->size == 1) {
        deque->first = NULL;
        deque->last = NULL;
    } else {
        deque->last->next = NULL;
    }

    deque->size--;
    free(last);
    return last_data;
}

static void *proper_pop_front(Deque* deque) {
    assert(deque != NULL);

    if (deque->size == 0) {
        return NULL;
    }

    Node *first = deque->first;
    void *first_data = first->data;
    deque->first = first->next;

    if (deque->size == 1) {
        deque->last = NULL;
    } else {
        deque->first->prev = NULL;
    }

    deque->size--;
    free(first);
    return first_data;
}

void push(Deque *deque, void* data) {
    assert(deque != NULL);
    if (deque->reversed) {
        proper_push_front(deque, data);
    } else {
        proper_push(deque, data);
    }
}

void push_front(Deque *deque, void *data) {
    assert(deque != NULL);
    if (deque->reversed) {
        proper_push(deque, data);
    } else {
        proper_push_front(deque, data);
    }
}

void *pop(Deque *deque) {
    assert(deque != NULL);
    if (deque->reversed) {
        return proper_pop_front(deque);
    } else {
        return proper_pop(deque);
    }
}

void *pop_front(Deque *deque) {
    assert(deque != NULL);
    if (deque->reversed) {
        return proper_pop(deque);
    } else {
        return proper_pop_front(deque);
    }
}

int size(Deque *deque) {
    assert(deque != NULL);
    return deque->size;
}

bool is_empty(Deque *deque) {
    assert(deque != NULL);
    return !(deque->size);
}

void reverse(Deque *deque) {
    assert(deque != NULL);
    if (deque->size > 1) {
        deque->reversed = !(deque->reversed);
    }
}

void print_deque(Deque *deque, void(*printFunc)(void*)) {
    if (deque == NULL) return;
    printf("[ ");

    Node *n;
    if (deque->reversed) {
        n = deque->last;
    } else {
        n = deque->first;
    }

    while(n != NULL) {
        printFunc(n->data);
        if (deque->reversed) {
            n = n->prev;
        } else {
            n = n->next;
        }
    }
    printf("]\n");
}

void destroy(Deque *deque) {
    if(deque == NULL) return;

    Node *cur = deque->first;
    while(cur != NULL) {
        Node *n = cur;
        cur = n->next;
        free(n);
    }

    free(deque);
}