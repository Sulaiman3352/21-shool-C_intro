#include "./list.h"

#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 0
#define FAIL 1

struct door* create_door(int id) {
    struct door* new_door = (struct door*)malloc(sizeof(struct door));
    if (!new_door) return NULL;
    new_door->id = id;
    return new_door;
}

int test_add_door() {
    struct door* door1 = create_door(1);
    struct node* list = init(door1);
    if (!list) return FAIL;

    struct door* door2 = create_door(2);
    const struct node* new_node = add_door(list, door2);
    if (!new_node || new_node->door->id != 2) return FAIL;

    destroy(list);
    return SUCCESS;
}

int test_remove_door() {
    struct door* door1 = create_door(1);
    struct door* door2 = create_door(2);
    struct door* door3 = create_door(3);

    struct node* list = init(door1);
    struct node* node2 = add_door(list, door2);
    add_door(node2, door3);

    list = remove_door(node2, list);
    if (find_door(2, list) != NULL) return FAIL;

    destroy(list);
    return SUCCESS;
}

void test() {
    struct door* door1 = (struct door*)malloc(sizeof(struct door));
    struct door* door2 = (struct door*)malloc(sizeof(struct door));

    struct node* list = init(door1);
    add_door(list, door2);

    destroy(list);
}

int main() {
    int result = SUCCESS;

    if (test_add_door() == FAIL) {
        printf("FAIL\n");
        result = FAIL;
    } else {
        printf("SUCCESS\n");
    }

    if (test_remove_door() == FAIL) {
        printf("FAIL\n");
        result = FAIL;
    } else {
        printf("SUCCESS\n");
    }
    test();
    return result;
}
