//
// Created by root on 8/31/17.
//
#include <iostream>
#include <string.h>
#include <zconf.h>
#include <stdlib.h>

using namespace std;

typedef struct List {
    void *data;
    List *next;
} List;

//get_data: List* -> void*
void *get_data(List *list) {
    return list->data;
}

//get_next: List* -> List*
List *get_next(List *list) {
    return list->next;
}

//set_data: void* X size_t X List* -> ()
void set_data(void *data, size_t size, List *list) {
    list->data = calloc(size, 1);
    memcpy(get_data(list), data, size);
}

//set_next: List* X List* -> ()
void set_next(List *next, List *list) {
    list->next = next;
}

//------------------------------------------------

//create_list: () -> List*
List *create_list() {
    List *list = (List *) calloc(1, sizeof(List));
    bzero(list, sizeof(List));
    return list;
}

//is_tail: List* -> bool
bool is_tail(List *list) {
    return get_data(list) == NULL &&
           get_next(list) == NULL;
}

//del_list: List* -> ()
void del_list(List *list) {
    List *tmp;

    if (is_tail(list)) {
        free(list);
        return;
    } else {
        tmp = get_next(list);
        free(get_data(list));
        free(list);
        return del_list(tmp);
    }
}

//add_list: List* X List* -> List*
List *add_list(List *pre_list, List *post_list) {
    List *pre_now = NULL;
    List *now     = pre_list;

    for (;;) {
        if (is_tail(now)) {
            del_list(now);
            if (pre_now == NULL) {
                return post_list;
            } else {
                set_next(post_list, pre_now);
                return pre_list;
            }
        } else {
            pre_now = now;
            now     = get_next(now);
        }
    }
}

//===================================================

//add_elem: void* X size_t X List* -> List*
List *add_elem(void *data, size_t size, List *list) {
    List *elem = create_list();

    set_data(data, size, elem);
    elem->next = list;
    return elem;
}

//del_elem: List* -> List*
List *del_elem(List *list) {
    List *tmp;

    if (is_tail(list)) {
        throw exception();
    } else {
        tmp = get_next(list);
        free(get_data(list));
        free(list);
        return tmp;
    }
}

void *iter_list(bool (*function_ptr1)(List *list),
                void *(*function_ptr2)(List *list),
                List *list) {
    if (is_tail(list)) {
        return function_ptr2(list);
    } else {
        if (function_ptr1(list)) {
            return list;
        } else {
            return iter_list(function_ptr1, function_ptr2, get_next(list));
        }
    }
}

bool display(List *list) {
    cout << *(int *) get_data(list) << endl;
    return false;
}

void *noooo(List *list) {

}

bool find2(void *data) {
    return *(int *) data == 2;
}

//void display(List *list) {
//    if (is_tail(list)) {
//        return;
//    } else {
//        cout << *(int *) get_data(list) << endl;
//        return display(get_next(list));
//    }
//}

int main() {
    int  num1   = 1;
    int  num2   = 2;
    int  num3   = 3;
    List *list  = create_list();
    List *list2 = create_list();
    List *tmp;

    list = add_elem(&num1, sizeof(num1), list);
    list = add_elem(&num2, sizeof(num2), list);
    list = add_elem(&num3, sizeof(num3), list);

    list2 = add_elem(&num1, sizeof(num1), list2);
    list2 = add_elem(&num2, sizeof(num2), list2);
    list2 = add_elem(&num3, sizeof(num3), list2);

    list2 = del_elem(list2);
    list2 = del_elem(list2);

    list = add_list(list, list2);

    iter_list(display, noooo, list);
//    tmp = (List *) iter_list(find2, list);

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
