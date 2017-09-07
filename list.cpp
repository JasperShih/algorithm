//
// Created by root on 8/31/17.
//
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct List {
    void *data;
    List *next;
} List;

//is_tail: List* -> bool
bool is_tail(List *list) {
    return list->next == NULL;
}

//----------------------------------------------------

//get_data: List* -> void*
void *get_data(List *list) {
    return list->data;
}

//get_next: List* -> List*
List *get_next(List *list) {
    if (is_tail(list)) {
        throw exception();
    } else {
        return list->next;
    }
}

//set_data: void* X size_t X List* -> ()
void set_data(void *data, size_t size, List *list) {
    free(get_data(list));
    list->data = calloc(size, 1);
    memcpy(get_data(list), data, size);
}

//set_next: List* X List* -> ()
void set_next(List *next, List *list) {
    list->next = next;
}

//----------------------------------------------------

//trans_to_list: void* X size_t -> List*
List *trans_to_list(void *data, size_t size) {
    List *list = (List *) calloc(1, sizeof(List));
    set_data(data, size, list);
    return list;
}

//add_elem: void* X size_t X List* -> List*
List *add_elem(void *data, size_t size, List *list) {
    List *elem = trans_to_list(data, size);
    set_next(list, elem);
    return elem;
}

//add_list: List* X List* -> List*
List *add_list(List *pre, List *post) {
    List *now = pre;

    for (;;) {
        if (is_tail(now)) {
            set_next(post, now);
            return pre;
        } else {
            now = get_next(now);
        }
    }
}

//del_elem: List* -> List*
List *del_elem(List *list) {
    List *tmp;

    if (is_tail(list)) {
        tmp = NULL;
    } else {
        tmp = get_next(list);
    }
    free(get_data(list));
    free(list);
    return tmp;
}

//del_list: List* -> ()
void del_list(List *list) {
    list = del_elem(list);
    if (list == NULL) {
        return;
    } else {
        return del_list(list);
    }
}

void display(List *list) {
    cout << *(int *) get_data(list) << endl;
    if (is_tail(list)) {
        return;
    } else {
        return display(get_next(list));
    }
}

int main() {
    int  num1   = 1;
    int  num2   = 2;
    int  num3   = 3;
    List *list  = trans_to_list(&num1, sizeof(num1));
    List *list2 = trans_to_list(&num1, sizeof(num1));

    list = add_elem(&num2, sizeof(num2), list);
    list = add_elem(&num3, sizeof(num3), list);

    list2 = add_elem(&num1, sizeof(num1), list2);
    list2 = add_elem(&num2, sizeof(num2), list2);
    list2 = add_elem(&num3, sizeof(num3), list2);

    list2 = del_elem(list2);
    list2 = del_elem(list2);

    list = add_list(list, list2);

    display(list);

    del_list(list);
}

/*
 * set
 * get
 * */

/*
 * create
 * tail?
 * add
 * del*/
