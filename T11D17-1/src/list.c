#include "list.h"

#include <stdlib.h>

struct node* init(struct door* door) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) return NULL;

    new_node->door = door;
    new_node->next = NULL;

    return new_node;
}

struct node* add_door(struct node* elem, struct door* door) {
    if (!elem) return NULL;

    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) return NULL;

    new_node->door = door;
    new_node->next = elem->next;
    elem->next = new_node;

    return new_node;
}

struct node* find_door(int door_id, struct node* root) {
    while (root) {
        if (root->door->id == door_id) {
            return root;
        }
        root = root->next;
    }
    return NULL;
}

struct node* remove_door(struct node* elem, struct node* root) {
    if (!root || !elem) return root;

    if (root == elem) {
        struct node* new_root = root->next;
        free(root);
        return new_root;
    }

    struct node* prev = root;
    while (prev->next && prev->next != elem) {
        prev = prev->next;
    }

    if (prev->next == elem) {
        prev->next = elem->next;
        free(elem->door);
        free(elem);
    }

    return root;
}

void destroy(struct node* root) {
    while (root) {
        struct node* temp = root;
        free(temp->door);
        root = root->next;
        free(temp);
    }
}